#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <wrl.h>

#include <stdexcept>
#include <utility>
#include <vector>

using Microsoft::WRL::ComPtr;

class DxAssist
{
public:
    DxAssist();
    DxAssist(const DxAssist&) = delete;
    DxAssist& operator=(const DxAssist&) = delete;

    ComPtr<ID3D12GraphicsCommandList> CreateCommandList(ID3D12CommandAllocator* command_allocator);
    ComPtr<ID3D12CommandAllocator>    CreateCommandAllocator();
    ComPtr<ID3D12Fence>               CreateFence();
    ComPtr<ID3D12Resource>            CreateReadBackBuffer(UINT64 size);
    ComPtr<ID3D12Resource>            CreateUploadBuffer(UINT64 size, void* data = nullptr);

    ComPtr<ID3D12Resource>            CreateUAVBuffer(UINT64                size,
                                                      D3D12_RESOURCE_STATES initial_state = D3D12_RESOURCE_STATE_UNORDERED_ACCESS);

    ID3D12Device*       device() { return device_.Get(); }
    ID3D12CommandQueue* command_queue() { return command_queue_.Get(); }


private:
    void InitDX12();
    void InitDXGI(D3D_FEATURE_LEVEL feature_level);
    void InitD3D(D3D_FEATURE_LEVEL feature_level);

    ComPtr<IDXGIFactory4>       dxgi_factory_      = nullptr;
    ComPtr<IDXGIAdapter>        dxgi_adapter_      = nullptr;
    ComPtr<ID3D12Device>        device_            = nullptr;
    ComPtr<ID3D12CommandQueue>  command_queue_     = nullptr;
};
