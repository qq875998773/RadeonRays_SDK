#pragma once

#include <string>
#include <vector>

#include "common.h"
#include "dxcapi.h"


using Microsoft::WRL::ComPtr;

struct Shader
{
    operator D3D12_SHADER_BYTECODE() const
    {
        return D3D12_SHADER_BYTECODE{dxc_blob->GetBufferPointer(), dxc_blob->GetBufferSize()};
    }

    ComPtr<IDxcBlob> dxc_blob;
};

class ShaderCompiler
{
public:
    static ShaderCompiler& instance();

    Shader CompileFromFile(const std::string& file_name,
                           const std::string& shader_model,
                           const std::string& entry_point);

    Shader CompileFromFile(const std::string&              file_name,
                           const std::string&              shader_model,
                           const std::string&              entry_point,
                           const std::vector<std::string>& defines);

    Shader CompileFromString(const std::string& source_string,
                             const std::string& shader_model,
                             const std::string& entry_point);

    Shader CompileFromString(const std::string&              source_string,
                             const std::string&              shader_model,
                             const std::string&              entry_point,
                             const std::vector<std::string>& defines);

private:
    ShaderCompiler();
    ~ShaderCompiler();

    HMODULE             hdll_;
    IDxcCompiler2*      compiler_        = nullptr;
    IDxcLibrary*        library_         = nullptr;
    IDxcIncludeHandler* include_handler_ = nullptr;
};

// Helper API function.
void CompileShader(const char*  path,
                   const char*  entry_point,
                   const char** defines,
                   uint32_t     num_defines,
                   void*        data,
                   size_t*      data_size);