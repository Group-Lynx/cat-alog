#ifndef CRYPTO_H
#define CRYPTO_H

#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

// Secret Secure Paw - ����צ�����㷨
namespace SSP
{
    const uint32_t K[4] = { 0x44417AA1, 0x77733BAD, 0x437E34CB, 0x78955737 };
    uint32_t rotl(uint32_t x, uint32_t r);
    std::string Encrypt(std::string _plain);
}

// ѭ�����ơ�
uint32_t SSP::rotl(uint32_t x, uint32_t r)
{
    return (x << r) | (x >> (32 - r));
}

// Ϊָ���ַ������ܡ�
std::string SSP::Encrypt(std::string _plain)
{
    std::vector<uint32_t> chunk;
    
    // �з��ַ���Ϊ����Ϊ 4 �Ŀ顣
    for (int i = 0; i < _plain.length(); i++)
    {
        if (i % 4 == 0)
        {
            chunk.push_back(_plain[i]);
            continue;
        }
        chunk[chunk.size() - 1] = chunk[chunk.size() - 1] * 0x3B + _plain[i];
    }
    
    // ʹ���ڿ�������ݻ�����
    for (int i = 0; i < chunk.size(); i++)
    {
        if (i == 0)
        {
            chunk[0] ^= rotl(chunk[chunk.size() - 1], 4);
            continue;
        }
        chunk[i] ^= rotl(chunk[i - 1], 4);
    }
    
    // ʹ����Կ�������ݻ�����
    uint32_t value[8] = {0};
    for (int i = 0; i < chunk.size(); i++)
    {
        value[0] ^= chunk[i] * K[0];
        value[1] += chunk[i] ^ K[1];
        value[2] ^= chunk[i] * K[2];
        value[3] += chunk[i] ^ K[3];
        value[4] ^= rotl(chunk[i], 4) * K[0];
        value[5] += rotl(chunk[i], 8) * K[1];
        value[6] ^= rotl(chunk[i], 12) * K[2];
        value[7] += rotl(chunk[i], 16) * K[3];
        
        for (int j = 1; j < 8; j++)
        {
            value[j] ^= rotl(value[j - 1], 4);
        }
        value[0] ^= rotl(value[7], 4);
    }
    
    // �������ġ�
    std::stringstream _cipher;
    for (int i = 0; i < 8; i++)
    {
        _cipher << std::hex << std::uppercase << std::setfill('0') << std::setw(8) << value[i];
    }
    
    return _cipher.str();
}

#endif