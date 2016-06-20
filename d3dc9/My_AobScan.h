#pragma once


bool bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask)
			return false;
	return (*szMask) == NULL;
}
DWORD FindPattern(DWORD dValor, DWORD dLer, BYTE *bMaskara, char * szMaskara)
{
	for (DWORD i = 0; i < dLer; i++)
		if (bCompare((PBYTE)(dValor + i), bMaskara, szMaskara))
			return (DWORD)(dValor + i);
	return false;
}



