#include "PX_Syntax_numeric.h"

PX_SYNTAX_FUNCTION(PX_Syntax_Parse_numeric)
{
	px_abi* plastabi;
	const px_char* pname;
	plastabi = PX_Syntax_GetAbiStack(pSyntax, -1);
	if (!plastabi)
	{
		PX_ASSERT();
		return PX_FALSE;
	}
	pname = PX_AbiGet_string(plastabi, "name");
	if (!pname)
	{
		PX_ASSERT();
		return PX_FALSE;
	}

	if (PX_strequ(pname, "const_int")|| PX_strequ(pname, "const_float"))
	{
		px_abi* pnewabi = PX_Syntax_PushNewAbi(pSyntax, "const_numeric", pSyntax->lifetime);
		if (!pnewabi)
		{
			PX_Syntax_Terminate(pSyntax, past, "Memory Error");
			return PX_FALSE;
		}
		if (!PX_AbiSet_Abi(pnewabi, "value", plastabi))
		{
			PX_Syntax_Terminate(pSyntax, past, "Memory Error");
			return PX_FALSE;
		}
		PX_Syntax_PopSecondAbiStack(pSyntax);
		return PX_TRUE;
	}
	
	PX_ASSERT();
	return PX_FALSE;
}

px_bool PX_Syntax_Load_numeric(PX_Syntax* pSyntax)
{

	if (!PX_Syntax_Parse_PEBNF(pSyntax, "const_numeric = const_int", PX_Syntax_Parse_numeric))
		return PX_FALSE;

	if (!PX_Syntax_Parse_PEBNF(pSyntax, "const_numeric = const_float", PX_Syntax_Parse_numeric))
		return PX_FALSE;

	return PX_TRUE;
}