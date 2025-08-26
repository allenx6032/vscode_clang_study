-- Path: test.lua
function myJump()
    print("jump() called from C++")
    a = jump(500)
    print("I Jumped during " , a , "ms!")
end

function myPrint(str, num)
    print("myPrint()")
    for i = 1, num do
        print(str)
    end
end

function myAdd(a, b)
    print("myAdd()")
    print("a = " .. a)
    print("b = " .. b)
    print("a + b = " .. a + b)
    return a + b
end

function myGetValue()
    print("myGetValue()")
    return 123
end

function myGetValues()
    print("myGetValues()")
    return 1, 2, 3
end

function myPrintTable(t)
    print("myPrintTable()")
    for k, v in pairs(t) do
        print(k, " = ", v)
    end
end

function myGetTable()
    print("myGetTable()")
    return 56, {str = "hello", num = 123, bool = true}, 3, 18, 72
end

function myGetArray()
    print("myGetArray()")
    return 56, {"hello", 123, true}, 3, 18, 72
end
