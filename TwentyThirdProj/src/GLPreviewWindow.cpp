#include "GLPreviewWindow.h"
#include "AppState.h"
#include "GLWindow.h"

#include <glm/gtc/matrix_transform.hpp>

using glm::ortho;
using glm::perspective;

namespace Coconut
{
    GLPreviewWindow::GLPreviewWindow(AppState* project)
        : ImGuiWidget(project, "Work Area"),
          mFBO(0),
          mTexture(0),
          mDepthStencilBuffer(0),
          mLastContentAreaSize(ImVec2(10.0,10.0)),
          mContentAreaSize(ImVec2(10.0,10.0)),
          mCameraPosition(0.f,50.f,-50.f),
          mCameraSpeedScale(50.f),
          mCameraPitchMax(glm::radians(45.f)),
          mCameraTarget(0.f,0.f,0.f),
          mCameraRadius(200.f),
          mCameraRadiusMin(10.f),
          mCameraPitch(glm::radians(45.0f)),
          mCameraYaw(glm::radians(-90.0f)),
          mUpVector(0.f,0.f,1.f),
          mViewMatrix(mat4(1.0f)),
          mProjectionMatrix(mat4(1.0f)),
          mNearClip(.1f),
          mFarClip(1000.f),
          mProjectionType(Perspective),
          mFollowTool(true)
    {
        UpdateCameraPosition();
    }

    void GLPreviewWindow::SetCameraTarget(const vec3& v)
    {
       mCameraTarget = v;
    }

    void GLPreviewWindow::SetCameraPosition(const vec3& v)
    {
       mCameraPosition = v;
    }


    GLPreviewWindow::~GLPreviewWindow ()
	{
        if (mDepthStencilBuffer > 0)
        {
            glDeleteRenderbuffers(1,&mDepthStencilBuffer);
            mDepthStencilBuffer = 0;
        }
        if (mTexture > 0)
        {
            glDeleteTextures(1, &mTexture);
        }
        if (mFBO > 0)
        {
           glDeleteFramebuffers(1,&mFBO);
        }
        GLCheckError();
    }

    bool GLPreviewWindow::InitGL()
    {
        if (!InitFramebuffer())
        {
            return false;
        }

        if(!InitTexture())
        {
            return false;
        }

        if (!InitDepthStencilBuffer())
        {
            return false;
        }

        BindFramebuffer();

        return true;
    }

    bool GLPreviewWindow::InitFramebuffer()
	{
		// Create Window Framebuffer
        glGenFramebuffers(1, &mFBO);
        if (mFBO == 0)
        {
            error("PreviewWindow: Error creating framebuffer");
            return false;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
        {
            error("Window: Unable to create window framebuffer");
        	GLCheckError();
        	glBindFramebuffer(GL_FRAMEBUFFER,0);
			return false;
        }

        GLCheckError();
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        return true;
    }

    bool GLPreviewWindow::InitDepthStencilBuffer()
    {
       if (mDepthStencilBuffer > 0)
       {
           glDeleteRenderbuffers(1,&mDepthStencilBuffer);
           mDepthStencilBuffer = 0;
       }

      	glGenRenderbuffers(1,&mDepthStencilBuffer);

        if (glGenRenderbuffers == 0)
        {
            error("GLPreviewWindow: Unable to create depth buffer");
            GLCheckError();
            return false;
        }

        glBindRenderbuffer(GL_RENDERBUFFER, mDepthStencilBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,
        	GetContentAreaWidth(), GetContentAreaHeight());

		glBindRenderbuffer(GL_RENDERBUFFER, 0);

       return true;
    }

    bool GLPreviewWindow::InitTexture()
    {
        // Clear Existing Texture
        if (mTexture != 0)
        {
            glDeleteTextures(1,&mTexture);
            mTexture = 0;
        }

        // Create Target Texture
        glGenTextures(1, &mTexture);
        if (mTexture == 0)
        {
            error("PreviewWindow: Unable to create texture");
            GLCheckError();
            mTexture = 0;
            return false;
        }

        // Set Parameters
        glBindTexture(GL_TEXTURE_2D, mTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GetContentAreaWidth(), GetContentAreaHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Unbind
        glBindTexture(GL_TEXTURE_2D,0);

        return true;
    }

    bool GLPreviewWindow::BindFramebuffer()
    {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mDepthStencilBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        return true;
    }

    void GLPreviewWindow::InitViewMatrix()
    {
        mViewMatrix = glm::lookAt(
            mCameraPosition, // the position of your camera, in world space
            mCameraTarget,   // where you want to look at, in world space
            mUpVector        // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
        );
    }

     void GLPreviewWindow::InitProjectionMatrix()
    {
        switch (mProjectionType)
        {
            case Ortho:
                // left, right, top, bottom, near, far
				mProjectionMatrix = ortho(
					0.f, (float)mContentAreaSize.x,
					0.f, (float)mContentAreaSize.y,
					mNearClip, mFarClip);
                break;
            case Perspective:
                // FOV, Aspect, Near, Far
				mProjectionMatrix = perspective(
            		glm::radians(45.0f),
					(float)mContentAreaSize.x / (float)mContentAreaSize.y,
					mNearClip, mFarClip);
                break;
        }
    }

     void GLPreviewWindow::UpdateCameraPosition()
     {
        mCameraPosition.x = (cos(mCameraYaw)*cos(mCameraPitch))*mCameraRadius;
        mCameraPosition.y = (sin(mCameraYaw)*cos(mCameraPitch))*mCameraRadius;
        mCameraPosition.z = sin(mCameraPitch)*mCameraRadius;

        InitViewMatrix();
        //info("GLPreviewDrawer: Cam at {},{},{}",mCameraPosition.x, mCameraPosition.y, mCameraPosition.z);
     }

    void GLPreviewWindow::Draw()
    {
        mLastContentAreaSize.x = mContentAreaSize.x;
        mLastContentAreaSize.y = mContentAreaSize.y;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,ImVec2(0.0f,0.0f));
        ImGui::Begin(mName.c_str(), &mVisible);
        mContentAreaSize = ImGui::GetContentRegionAvail();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::Image((void*)(intptr_t)mTexture,mContentAreaSize,UV1, UV2);
        if (ImGui::IsItemHovered())
		{
            if(ImGui::IsMouseDragging())
            {
                ImVec2 delta = ImGui::GetIO().MouseDelta;
                mCameraPitch += delta.y / mCameraSpeedScale;
                mCameraYaw += delta.x / mCameraSpeedScale;
            }

            mCameraRadius += io.MouseWheel / mCameraSpeedScale;

            // Clamping

            if (mCameraPitch > mCameraPitchMax) mCameraPitch = mCameraPitchMax;
            else if (mCameraPitch < -mCameraPitchMax) mCameraPitch = -mCameraPitchMax;

            if (mCameraRadius < mCameraRadiusMin) mCameraRadius = mCameraRadiusMin;

            debug("GLPreviewWindow: pitch {} yaw {} radius {}", mCameraPitch, mCameraYaw, mCameraRadius);
		}

        UpdateCameraPosition();

		ImGui::End();
        ImGui::PopStyleVar();
    }

    float GLPreviewWindow::GetContentAreaWidth()
    {
		return mContentAreaSize.x;
    }

    float GLPreviewWindow::GetContentAreaHeight()
    {
		return mContentAreaSize.y;
    }

    bool GLPreviewWindow::PreviewSizeHasChanged()
    {
        return mContentAreaSize.x != mLastContentAreaSize.x ||
                mContentAreaSize.y != mLastContentAreaSize.y;
    }

    GLuint GLPreviewWindow::GetFBO()
    {
       return mFBO;
    }

    mat4 GLPreviewWindow::GetViewMatrix()
    {
        return mViewMatrix;
    }

    mat4 GLPreviewWindow::GetProjectionMatrix()
    {
        return mProjectionMatrix;
    }

	ImVec2 GLPreviewWindow::UV1 = ImVec2(0,1);
	ImVec2 GLPreviewWindow::UV2 = ImVec2(1,0);

}

