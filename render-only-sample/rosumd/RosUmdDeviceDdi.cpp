#include "RosUmdDeviceDdi.h"
#include "RosUmdDevice.h"
#include "RosUmdResource.h"
#include "RosUmdDebug.h"
#include "RosUmdLogging.h"
#include "RosUmdRasterizerState.h"
#include "RosUmdDepthStencilState.h"
#include "RosUmdSampler.h"
#include "RosUmdElementLayout.h"
#include "RosUmdShader.h"
#include "RosUmdBlendState.h"
#include "RosUmdRenderTargetView.h"

#include "RosContext.h"

#include <exception>
#include <typeinfo>
#include <new>

//
// Ddi Tables
//

const D3D11_1DDI_DEVICEFUNCS RosUmdDeviceDdi::s_deviceFuncs11_1 =
{
    RosUmdDeviceDdi::DefaultConstantBufferUpdateSubresourceUP11_1_Default,
    RosUmdDeviceDdi::VsSetConstantBuffers11_1_Default,
    RosUmdDeviceDdi::PSSetShaderResources_Default,
    RosUmdDeviceDdi::DdiPsSetShader,
    RosUmdDeviceDdi::DdiPSSetSamplers,
    RosUmdDeviceDdi::DdiVsSetShader,
    RosUmdDeviceDdi::DdiDrawIndexed,
    RosUmdDeviceDdi::DdiDraw,
    RosUmdDeviceDdi::DynamicIABufferMapNoOverwrite_Default,
    RosUmdDeviceDdi::DynamicIABufferUnmap_Default,
    RosUmdDeviceDdi::DynamicConstantBufferMapDiscard_Default,
    RosUmdDeviceDdi::DynamicIABufferMapDiscard_Default,
    RosUmdDeviceDdi::DynamicConstantBufferUnmap_Default,
    RosUmdDeviceDdi::PsSetConstantBuffers11_1_Default,
    RosUmdDeviceDdi::DdiIaSetInputLayout,
    RosUmdDeviceDdi::DdiIaSetVertexBuffers,
    RosUmdDeviceDdi::DdiIaSetIndexBuffer,

    RosUmdDeviceDdi::DrawIndexedInstanced_Dirty,
    RosUmdDeviceDdi::DrawInstanced_Dirty,
    RosUmdDeviceDdi::DynamicResourceMapDiscard_Default,
    RosUmdDeviceDdi::DynamicResourceUnmap_Default,
    RosUmdDeviceDdi::GsSetConstantBuffers11_1_Default,
    RosUmdDeviceDdi::DdiGsSetShader,
    RosUmdDeviceDdi::DdiIaSetTopology,
    RosUmdDeviceDdi::DdiStagingResourceMap,
    RosUmdDeviceDdi::DdiStagingResourceUnmap,
    RosUmdDeviceDdi::VSSetShaderResources_Default,
    RosUmdDeviceDdi::DdiVSSetSamplers,
    RosUmdDeviceDdi::GSSetShaderResources_Default,
    RosUmdDeviceDdi::DdiGSSetSamplers,
    RosUmdDeviceDdi::DdiSetRenderTargets,
    RosUmdDeviceDdi::ShaderResourceViewReadAfterWriteHazard_Default,
    RosUmdDeviceDdi::ResourceReadAfterWriteHazard_Default,
    RosUmdDeviceDdi::DdiSetBlendState,
    RosUmdDeviceDdi::DdiSetDepthStencilState,
    RosUmdDeviceDdi::DdiSetRasterizerState,
    RosUmdDeviceDdi::QueryEnd_Default,
    RosUmdDeviceDdi::QueryBegin_Default,
    RosUmdDeviceDdi::ResourceCopyRegion11_1_Default,
    RosUmdDeviceDdi::ResourceUpdateSubresourceUP11_1_Default,
    RosUmdDeviceDdi::SOSetTargets_Default,
    RosUmdDeviceDdi::DrawAuto_Dirty,
    RosUmdDeviceDdi::DdiSetViewports,
    RosUmdDeviceDdi::SetScissorRects_Default,
    RosUmdDeviceDdi::DdiClearRenderTargetView,
    RosUmdDeviceDdi::ClearDepthStencilView_Default,
    RosUmdDeviceDdi::SetPredication_Default,
    RosUmdDeviceDdi::QueryGetData_Default,
    RosUmdDeviceDdi::DdiFlush,
    RosUmdDeviceDdi::GenerateMips_Default,
    RosUmdDeviceDdi::DdiResourceCopy,
    RosUmdDeviceDdi::ResourceResolveSubresource_Default,

    RosUmdDeviceDdi::ResourceMap_Default,
    RosUmdDeviceDdi::ResourceUnmap_Default,
    RosUmdDeviceDdi::ResourceIsStagingBusy_Default,
    RosUmdDeviceDdi::RelocateDeviceFuncs11_1_Default,
    RosUmdDeviceDdi::DdiCalcPrivateResourceSize,
    RosUmdDeviceDdi::CalcPrivateOpenedResourceSize_Default,
    RosUmdDeviceDdi::DdiCreateResource,
    RosUmdDeviceDdi::OpenResource_Default,
    RosUmdDeviceDdi::DdiDestroyResource,
    RosUmdDeviceDdi::CalcPrivateShaderResourceViewSize11_Default,
    RosUmdDeviceDdi::CreateShaderResourceView11_Default,
    RosUmdDeviceDdi::DestroyShaderResourceView_Default,
    RosUmdDeviceDdi::DdiCalcPrivateRenderTargetViewSize,
    RosUmdDeviceDdi::DdiCreateRenderTargetView,
    RosUmdDeviceDdi::DdiDestroyRenderTargetView,
    RosUmdDeviceDdi::CalcPrivateDepthStencilViewSize11_Default,
    RosUmdDeviceDdi::CreateDepthStencilView11_Default,
    RosUmdDeviceDdi::DestroyDepthStencilView_Default,
    RosUmdDeviceDdi::DdiCalcPrivateElementLayoutSize,
    RosUmdDeviceDdi::DdiCreateElementLayout,
    RosUmdDeviceDdi::DdiDestroyElementLayout,
    RosUmdDeviceDdi::DdiCalcPrivateBlendStateSize,
    RosUmdDeviceDdi::DdiCreateBlendState,
    RosUmdDeviceDdi::DdiDestroyBlendState,
    RosUmdDeviceDdi::DdiCalcPrivateDepthStencilStateSize,
    RosUmdDeviceDdi::DdiCreateDepthStencilState,
    RosUmdDeviceDdi::DdiDestroyDepthStencilState,
    RosUmdDeviceDdi::DdiCalcRasterizerStateSize,
    RosUmdDeviceDdi::DdiCreateRasterizerState,
    RosUmdDeviceDdi::DdiDestroyRasterizerState,
    RosUmdDeviceDdi::DdiCalcPrivateShaderSize,
    RosUmdDeviceDdi::DdiCreateVertexShader,
    RosUmdDeviceDdi::DdiCreateGeometryShader,
    RosUmdDeviceDdi::DdiCreatePixelShader,
    RosUmdDeviceDdi::CalcPrivateGeometryShaderWithStreamOutputSize11_1_Default,
    RosUmdDeviceDdi::CreateGeometryShaderWithStreamOutput11_1_Default,
    RosUmdDeviceDdi::DdiDestroyShader,
    RosUmdDeviceDdi::DdiCalcPrivateSamplerSize,
    RosUmdDeviceDdi::DdiCreateSampler,
    RosUmdDeviceDdi::DdiDestroySampler,
    RosUmdDeviceDdi::CalcPrivateQuerySize_Default,
    RosUmdDeviceDdi::CreateQuery_Default,
    RosUmdDeviceDdi::DestroyQuery_Default,

    RosUmdDeviceDdi::DdiCheckFormatSupport,
    RosUmdDeviceDdi::DdiCheckMultisampleQualityLevels,
    RosUmdDeviceDdi::DdiCheckCounterInfo,
    RosUmdDeviceDdi::CheckCounter_Default,
    RosUmdDeviceDdi::DdiDestroyDevice,
    RosUmdDeviceDdi::SetTextFilter_Default,
    RosUmdDeviceDdi::DdiResourceCopy,
    RosUmdDeviceDdi::ResourceCopyRegion11_1_Default,

    RosUmdDeviceDdi::DrawIndexedInstancedIndirect_Dirty,
    RosUmdDeviceDdi::DrawInstancedIndirect_Dirty,
    NULL, // RosUmdDeviceDdi::CommandListExecute_Default,
    RosUmdDeviceDdi::HSSetShaderResources_Default,
    RosUmdDeviceDdi::DdiHsSetShader,
    RosUmdDeviceDdi::DdiHSSetSamplers,
    RosUmdDeviceDdi::HsSetConstantBuffers11_1_Default,
    RosUmdDeviceDdi::DSSetShaderResources_Default,
    RosUmdDeviceDdi::DdiDsSetShader,
    RosUmdDeviceDdi::DdiDSSetSamplers,
    RosUmdDeviceDdi::DsSetConstantBuffers11_1_Default,
    RosUmdDeviceDdi::DdiCreateHullShader,
    RosUmdDeviceDdi::DdiCreateDomainShader,
    NULL, // RosUmdDeviceDdi::CheckDeferredContextHandleSizes_Default,
    NULL, // RosUmdDeviceDdi::CalcDeferredContextHandleSize_Default,
    NULL, // RosUmdDeviceDdi::CalcPrivateDeferredContextSize_Default,
    NULL, // RosUmdDeviceDdi::CreateDeferredContext_Default,
    NULL, // RosUmdDeviceDdi::AbandonCommandList_Default,
    NULL, // RosUmdDeviceDdi::CalcPrivateCommandListSize_Default,
    NULL, // RosUmdDeviceDdi::CreateCommandList_Default,
    NULL, // RosUmdDeviceDdi::DestroyCommandList_Default,
    RosUmdDeviceDdi::DdiCalcPrivateTessellationShaderSize,
    RosUmdDeviceDdi::PsSetShaderWithInterfaces_Default,
    RosUmdDeviceDdi::VsSetShaderWithInterfaces_Default,
    RosUmdDeviceDdi::GsSetShaderWithInterfaces_Default,
    RosUmdDeviceDdi::HsSetShaderWithInterfaces_Default,
    RosUmdDeviceDdi::DsSetShaderWithInterfaces_Default,
    RosUmdDeviceDdi::CsSetShaderWithInterfaces_Default,
    RosUmdDeviceDdi::DdiCreateComputeShader,
    RosUmdDeviceDdi::DdiCsSetShader,
    RosUmdDeviceDdi::CSSetShaderResources_Default,
    RosUmdDeviceDdi::DdiCSSetSamplers,
    RosUmdDeviceDdi::CsSetConstantBuffers11_1_Default,
    RosUmdDeviceDdi::CalcPrivateUnorderedAccessViewSize_Default,
    RosUmdDeviceDdi::CreateUnorderedAccessView_Default,
    RosUmdDeviceDdi::DestroyUnorderedAccessView_Default,
    RosUmdDeviceDdi::ClearUnorderedAccessViewUint_Default,
    RosUmdDeviceDdi::ClearUnorderedAccessViewFloat_Default,
    RosUmdDeviceDdi::CSSetUnorderedAccessViews_Default,
    RosUmdDeviceDdi::Dispatch_Dirty,
    RosUmdDeviceDdi::DispatchIndirect_Dirty,
    RosUmdDeviceDdi::SetResourceMinLOD_Default,
    RosUmdDeviceDdi::CopyStructureCount_Default,
    NULL, // RosUmdDeviceDdi::RecycleCommandList_Default,
    NULL, // RosUmdDeviceDdi::RecycleCreateCommandList_Default,
    NULL, // RosUmdDeviceDdi::RecycleCreateDeferredContext_Default,
    NULL, // RosUmdDeviceDdi::RecycleDestroyCommandList_Default,
    RosUmdDeviceDdi::Discard_Default,
    RosUmdDeviceDdi::AssignDebugBinary_Default,
    RosUmdDeviceDdi::DynamicConstantBufferMapNoOverwrite_Default,
    NULL, // PFND3D11_1DDI_CHECKDIRECTFLIPSUPPORT
    RosUmdDeviceDdi::ClearView_Default,
};

const DXGI1_2_DDI_BASE_FUNCTIONS RosUmdDeviceDdi::s_dxgiDeviceFuncs3 =
{
    NULL, // RosUmdDeviceDdi::Present,          //Present
    NULL, // RosUmdDeviceDdi::GetGammaCaps,     //GetGammaCaps
    NULL, // RosUmdDeviceDdi::SetDisplayMode,   //SetDisplayMode
    NULL, // RosUmdDeviceDdi::SetResourcePriority,
    NULL, // RosUmdDeviceDdi::QueryResourceResidency,
    NULL, // RosUmdDeviceDdi::RotateResourceIdentities,
    NULL, // RosUmdDeviceDdi::Blt,
    NULL, // RosUmdDeviceDdi::ResolveSharedResource,
    NULL, // RosUmdDeviceDdi::Blt1,
    NULL, // pfnOfferResources
    NULL, // pfnReclaimResources
};

//
// DDI entry points
//

void APIENTRY RosUmdDeviceDdi::DdiDestroyDevice(
    D3D10DDI_HDEVICE hDevice)
{
    RosUmdLogging::Entry(__FUNCTION__);

    RosUmdDevice* pRosUmdDevice = RosUmdDevice::CastFrom(hDevice);

    try {
        pRosUmdDevice->Teardown();
        pRosUmdDevice->~RosUmdDevice();
    }

    catch (std::exception &)
    {
        // do nothing
    }

    RosUmdLogging::Exit(__FUNCTION__);
}

void APIENTRY RosUmdDeviceDdi::DdiCreateResource(
    D3D10DDI_HDEVICE hDevice,
    const D3D11DDIARG_CREATERESOURCE* pCreateResource,
    D3D10DDI_HRESOURCE hResource,
    D3D10DDI_HRTRESOURCE hRTResource)
{
    RosUmdLogging::Entry(__FUNCTION__);

    RosUmdDevice* pRosUmdDevice = RosUmdDevice::CastFrom(hDevice);

    try {
        pRosUmdDevice->CreateResource(pCreateResource, hResource, hRTResource);
    }

    catch (std::exception & e)
    {
        pRosUmdDevice->SetException(e);
    }

    RosUmdLogging::Exit(__FUNCTION__);
}

void APIENTRY RosUmdDeviceDdi::DdiDestroyResource(
    D3D10DDI_HDEVICE hDevice,
    D3D10DDI_HRESOURCE hResource)
{
    RosUmdLogging::Entry(__FUNCTION__);

    RosUmdDevice* pRosUmdDevice = RosUmdDevice::CastFrom(hDevice);

    RosUmdResource * pResource = (RosUmdResource *)hResource.pDrvPrivate;

    pRosUmdDevice->DestroyResource(pResource);

    RosUmdLogging::Exit(__FUNCTION__);
}

void APIENTRY RosUmdDeviceDdi::DdiResourceCopy(
    D3D10DDI_HDEVICE hDevice,
    D3D10DDI_HRESOURCE hDestinationResource,
    D3D10DDI_HRESOURCE hSourceResource)
{
    RosUmdLogging::Entry(__FUNCTION__);

    RosUmdDevice* pRosUmdDevice = RosUmdDevice::CastFrom(hDevice);
    RosUmdResource * pDestinationResource = (RosUmdResource *)hDestinationResource.pDrvPrivate;
    RosUmdResource * pSourceResource = (RosUmdResource *)hSourceResource.pDrvPrivate;

    try
    {
        pRosUmdDevice->ResourceCopy(pDestinationResource, pSourceResource);
    }

    catch (std::exception & e)
    {
        pRosUmdDevice->SetException(e);
    }

    RosUmdLogging::Exit(__FUNCTION__);
}

void APIENTRY RosUmdDeviceDdi::DdiStagingResourceMap(
    D3D10DDI_HDEVICE hDevice,
    D3D10DDI_HRESOURCE hResource,
    UINT subResource,
    D3D10_DDI_MAP mapType,
    UINT mapFlags,
    D3D10DDI_MAPPED_SUBRESOURCE* pMappedSubRes)
{
    RosUmdLogging::Entry(__FUNCTION__);

    RosUmdDevice* pRosUmdDevice = RosUmdDevice::CastFrom(hDevice);
    RosUmdResource * pResource = (RosUmdResource *)hResource.pDrvPrivate;

    try
    {
        pRosUmdDevice->StagingResourceMap(pResource, subResource, mapType, mapFlags, pMappedSubRes);
    }

    catch (std::exception & e)
    {
        pRosUmdDevice->SetException(e);
    }

    RosUmdLogging::Exit(__FUNCTION__);
}

void APIENTRY RosUmdDeviceDdi::DdiStagingResourceUnmap(
    D3D10DDI_HDEVICE hDevice,
    D3D10DDI_HRESOURCE hResource,
    UINT subResource)
{
    RosUmdLogging::Entry(__FUNCTION__);

    RosUmdDevice* pRosUmdDevice = RosUmdDevice::CastFrom(hDevice);
    RosUmdResource * pResource = (RosUmdResource *)hResource.pDrvPrivate;

    try
    {
        pRosUmdDevice->StagingResourceUnmap(pResource, subResource);
    }

    catch (std::exception & e)
    {
        pRosUmdDevice->SetException(e);
    }

    RosUmdLogging::Exit(__FUNCTION__);
}

BOOL APIENTRY RosUmdDeviceDdi::DdiFlush(D3D10DDI_HDEVICE hDevice, UINT flushFlags)
{
    RosUmdLogging::Entry(__FUNCTION__);

    RosUmdDevice* pRosUmdDevice = RosUmdDevice::CastFrom(hDevice);

    BOOL bSuccess = TRUE;

    try
    {
        pRosUmdDevice->m_commandBuffer.Flush(flushFlags);
    }

    catch (std::exception & e)
    {
        pRosUmdDevice->SetException(e);
        bSuccess = FALSE;
    }

    RosUmdLogging::Exit(__FUNCTION__);

    return bSuccess;
}

void APIENTRY RosUmdDeviceDdi::DdiCheckFormatSupport(
    D3D10DDI_HDEVICE hDevice,
    DXGI_FORMAT Format,
    UINT* pFormatSupport)
{
    // RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice* pRosUmdDevice = RosUmdDevice::CastFrom(hDevice);

    pRosUmdDevice->CheckFormatSupport(Format, pFormatSupport);
}

void APIENTRY RosUmdDeviceDdi::DdiCheckCounterInfo(
    D3D10DDI_HDEVICE hDevice,
    D3D10DDI_COUNTER_INFO* pCounterInfo)
{
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice* pRosUmdDevice = RosUmdDevice::CastFrom(hDevice);
    pRosUmdDevice->CheckCounterInfo(pCounterInfo);
}

void APIENTRY RosUmdDeviceDdi::DdiCheckMultisampleQualityLevels(
    D3D10DDI_HDEVICE hDevice,
    DXGI_FORMAT Format,
    UINT SampleCount,
    UINT* pNumQualityLevels)
{
    // RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice* pRosUmdDevice = RosUmdDevice::CastFrom(hDevice);
    pRosUmdDevice->CheckMultisampleQualityLevels(Format, SampleCount, pNumQualityLevels);
}

SIZE_T APIENTRY RosUmdDeviceDdi::DdiCalcPrivateResourceSize(
    D3D10DDI_HDEVICE,
    const D3D11DDIARG_CREATERESOURCE*)
{
    RosUmdLogging::Call(__FUNCTION__);

    return sizeof(RosUmdResource);
}

//
// Rasterizer State
//

SIZE_T APIENTRY RosUmdDeviceDdi::DdiCalcRasterizerStateSize(
    D3D10DDI_HDEVICE,
    const D3D11_1_DDI_RASTERIZER_DESC*)
{
    RosUmdLogging::Call(__FUNCTION__);

    return sizeof(RosUmdRasterizerState); 
}

void APIENTRY RosUmdDeviceDdi::DdiCreateRasterizerState(
    D3D10DDI_HDEVICE,
    const D3D11_1_DDI_RASTERIZER_DESC* desc,
    D3D10DDI_HRASTERIZERSTATE hRasterizerState,
    D3D10DDI_HRTRASTERIZERSTATE hRTRasterizerState) 
{ 
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdRasterizerState* pRasterizerState = new (hRasterizerState.pDrvPrivate) RosUmdRasterizerState(desc, hRTRasterizerState);
    pRasterizerState; // unused
}

void APIENTRY RosUmdDeviceDdi::DdiDestroyRasterizerState(
    D3D10DDI_HDEVICE hDevice,
    D3D10DDI_HRASTERIZERSTATE hRasterizerState) 
{
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    RosUmdRasterizerState * pRasterizerState = RosUmdRasterizerState::CastFrom(hRasterizerState);

    pDevice; // unused
    pRasterizerState; // unused
}

void APIENTRY RosUmdDeviceDdi::DdiSetRasterizerState(
    D3D10DDI_HDEVICE hDevice, 
    D3D10DDI_HRASTERIZERSTATE hRasterizerState)
{
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    RosUmdRasterizerState * pRasterizerState = RosUmdRasterizerState::CastFrom(hRasterizerState);
    pDevice->SetRasterizerState(pRasterizerState);
}

//
// Depth Stencil State
//

SIZE_T APIENTRY RosUmdDeviceDdi::DdiCalcPrivateDepthStencilStateSize(
    D3D10DDI_HDEVICE hDevice, 
    const D3D10_DDI_DEPTH_STENCIL_DESC* desc)
{ 
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice; // unused
    desc; // unused

    return sizeof(RosUmdDepthStencilState); 
}

void APIENTRY RosUmdDeviceDdi::DdiCreateDepthStencilState(
    D3D10DDI_HDEVICE hDevice,
    const D3D10_DDI_DEPTH_STENCIL_DESC* desc,
    D3D10DDI_HDEPTHSTENCILSTATE hDepthStencilState,
    D3D10DDI_HRTDEPTHSTENCILSTATE hRTDepthStencilState) 
{ 
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice; // unused

    RosUmdDepthStencilState* pDepthStencilState = new (hDepthStencilState.pDrvPrivate) RosUmdDepthStencilState(desc, hRTDepthStencilState);
    pDepthStencilState; // unused
}

void APIENTRY RosUmdDeviceDdi::DdiDestroyDepthStencilState(
    D3D10DDI_HDEVICE hDevice,
    D3D10DDI_HDEPTHSTENCILSTATE hDepthStencilState) 
{ 
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    RosUmdDepthStencilState * pDepthStencilState = RosUmdDepthStencilState::CastFrom(hDepthStencilState);

    pDevice; // unusd
    pDepthStencilState; // unused

}

void APIENTRY RosUmdDeviceDdi::DdiSetDepthStencilState(
    D3D10DDI_HDEVICE hDevice,
    D3D10DDI_HDEPTHSTENCILSTATE hDepthStencilState,
    UINT StencilRef) 
{ 
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    RosUmdDepthStencilState * pDepthStencilState = RosUmdDepthStencilState::CastFrom(hDepthStencilState);
    pDevice->SetDepthStencilState(pDepthStencilState, StencilRef);
}

//
// Sampler
//

SIZE_T APIENTRY RosUmdDeviceDdi::DdiCalcPrivateSamplerSize(
    D3D10DDI_HDEVICE hDevice, 
    const D3D10_DDI_SAMPLER_DESC* desc)
{ 
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice; // unused
    desc; // unused

    return sizeof(RosUmdSampler);
}

void APIENTRY RosUmdDeviceDdi::DdiCreateSampler(
    D3D10DDI_HDEVICE hDevice,
    const D3D10_DDI_SAMPLER_DESC* desc,
    D3D10DDI_HSAMPLER hSampler, 
    D3D10DDI_HRTSAMPLER hRTSampler)
{
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice; // unusd

    RosUmdSampler* pSampler = new (hSampler.pDrvPrivate) RosUmdSampler(desc, hRTSampler);
    pSampler; // unused
}

void APIENTRY RosUmdDeviceDdi::DdiDestroySampler(
    D3D10DDI_HDEVICE hDevice,
    D3D10DDI_HSAMPLER hSampler)
{ 
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice; // unusd

    RosUmdSampler * pSampler = RosUmdSampler::CastFrom(hSampler);
    pSampler; // unused
}

void APIENTRY RosUmdDeviceDdi::DdiPSSetSamplers(
    D3D10DDI_HDEVICE hDevice, 
    UINT Offset, 
    UINT NumSamplers,
    const D3D10DDI_HSAMPLER* phSamplers) 
{ 
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice->SetPixelSamplers(Offset, NumSamplers, phSamplers);
}

void APIENTRY RosUmdDeviceDdi::DdiVSSetSamplers(
    D3D10DDI_HDEVICE hDevice,
    UINT Offset,
    UINT NumSamplers,
    const D3D10DDI_HSAMPLER* phSamplers)
{
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice->SetVertexSamplers(Offset, NumSamplers, phSamplers);
}

void APIENTRY RosUmdDeviceDdi::DdiGSSetSamplers(
    D3D10DDI_HDEVICE hDevice,
    UINT Offset,
    UINT NumSamplers,
    const D3D10DDI_HSAMPLER* phSamplers)
{
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice->SetGeometrySamplers(Offset, NumSamplers, phSamplers);
}

void APIENTRY RosUmdDeviceDdi::DdiCSSetSamplers(
    D3D10DDI_HDEVICE hDevice,
    UINT Offset,
    UINT NumSamplers,
    const D3D10DDI_HSAMPLER* phSamplers)
{
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice->SetComputeSamplers(Offset, NumSamplers, phSamplers);
}

void APIENTRY RosUmdDeviceDdi::DdiHSSetSamplers(
    D3D10DDI_HDEVICE hDevice,
    UINT Offset,
    UINT NumSamplers,
    const D3D10DDI_HSAMPLER* phSamplers)
{
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice->SetHullSamplers(Offset, NumSamplers, phSamplers);
}

void APIENTRY RosUmdDeviceDdi::DdiDSSetSamplers(
    D3D10DDI_HDEVICE hDevice,
    UINT Offset,
    UINT NumSamplers,
    const D3D10DDI_HSAMPLER* phSamplers)
{
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice->SetDomainSamplers(Offset, NumSamplers, phSamplers);
}

//
// Element Layout
//

SIZE_T APIENTRY RosUmdDeviceDdi::DdiCalcPrivateElementLayoutSize(
    D3D10DDI_HDEVICE hDevice, 
    const D3D10DDIARG_CREATEELEMENTLAYOUT* pCreate) 
{ 
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice; // unused
    pCreate; // unused

    return sizeof(RosUmdElementLayout);
}

void APIENTRY RosUmdDeviceDdi::DdiCreateElementLayout(
    D3D10DDI_HDEVICE hDevice,
    const D3D10DDIARG_CREATEELEMENTLAYOUT* pCreate,
    D3D10DDI_HELEMENTLAYOUT hElementLayout,
    D3D10DDI_HRTELEMENTLAYOUT hRTElementLayout)
{ 
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice; // unused

    RosUmdElementLayout* pElementLayout = new (hElementLayout.pDrvPrivate) RosUmdElementLayout(pCreate, hRTElementLayout);
    pElementLayout; // unused
}

void APIENTRY RosUmdDeviceDdi::DdiDestroyElementLayout(
    D3D10DDI_HDEVICE hDevice,
    D3D10DDI_HELEMENTLAYOUT hElementLayout)
{ 
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice; // unused

    RosUmdElementLayout * pElementLayout = RosUmdElementLayout::CastFrom(hElementLayout);
    pElementLayout->~RosUmdElementLayout();

}

void APIENTRY RosUmdDeviceDdi::DdiIaSetInputLayout(
    D3D10DDI_HDEVICE hDevice,
    D3D10DDI_HELEMENTLAYOUT hElementLayout)
{
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    RosUmdElementLayout * pElementLayout = RosUmdElementLayout::CastFrom(hElementLayout);
    pDevice->SetElementLayout(pElementLayout);
}

//
// Shaders
//

SIZE_T APIENTRY RosUmdDeviceDdi::DdiCalcPrivateShaderSize(
    D3D10DDI_HDEVICE hDevice,
    const UINT* pCode,
    const D3D11_1DDIARG_STAGE_IO_SIGNATURES* pSignatures)
{ 
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice; // unused
    pCode; // unused
    pSignatures; // unused

    return sizeof(RosUmdPipelineShader);
}

void APIENTRY RosUmdDeviceDdi::DdiCreatePixelShader(
    D3D10DDI_HDEVICE hDevice,
    const UINT* pCode,
    D3D10DDI_HSHADER hShader,
    D3D10DDI_HRTSHADER hRTShader,
    const D3D11_1DDIARG_STAGE_IO_SIGNATURES* pSignatures)
{
    RosUmdLogging::Entry(__FUNCTION__);

    RosUmdDevice * pRosUmdDevice = RosUmdDevice::CastFrom(hDevice);

    try
    {
        pRosUmdDevice->CreatePixelShader(pCode, hShader, hRTShader, pSignatures);
    }

    catch (std::exception & e)
    {
        pRosUmdDevice->SetException(e);
    }

    RosUmdLogging::Exit(__FUNCTION__);
}

void APIENTRY RosUmdDeviceDdi::DdiCreateVertexShader(
    D3D10DDI_HDEVICE hDevice,
    const UINT* pCode,
    D3D10DDI_HSHADER hShader,
    D3D10DDI_HRTSHADER hRTShader,
    const D3D11_1DDIARG_STAGE_IO_SIGNATURES* pSignatures)
{
    RosUmdLogging::Entry(__FUNCTION__);

    RosUmdDevice * pRosUmdDevice = RosUmdDevice::CastFrom(hDevice);

    try
    {
        pRosUmdDevice->CreateVertexShader(pCode, hShader, hRTShader, pSignatures);
    }

    catch (std::exception & e)
    {
        pRosUmdDevice->SetException(e);
    }

    RosUmdLogging::Exit(__FUNCTION__);
}

void APIENTRY RosUmdDeviceDdi::DdiCreateGeometryShader(
    D3D10DDI_HDEVICE hDevice,
    const UINT* pCode,
    D3D10DDI_HSHADER hShader,
    D3D10DDI_HRTSHADER hRTShader,
    const D3D11_1DDIARG_STAGE_IO_SIGNATURES* pSignatures)
{
    RosUmdLogging::Entry(__FUNCTION__);

    RosUmdDevice * pRosUmdDevice = RosUmdDevice::CastFrom(hDevice);

    try
    {
        pRosUmdDevice->CreateGeometryShader(pCode, hShader, hRTShader, pSignatures);
    }

    catch (std::exception & e)
    {
        pRosUmdDevice->SetException(e);
    }

    RosUmdLogging::Exit(__FUNCTION__);
}

void APIENTRY RosUmdDeviceDdi::DdiCreateComputeShader(
    D3D10DDI_HDEVICE hDevice,
    const UINT* pCode,
    D3D10DDI_HSHADER hShader,
    D3D10DDI_HRTSHADER hRTShader)
{
    RosUmdLogging::Entry(__FUNCTION__);

    RosUmdDevice * pRosUmdDevice = RosUmdDevice::CastFrom(hDevice);

    try
    {
        pRosUmdDevice->CreateComputeShader(pCode, hShader, hRTShader);
    }

    catch (std::exception & e)
    {
        pRosUmdDevice->SetException(e);
    }

    RosUmdLogging::Exit(__FUNCTION__);
}

SIZE_T APIENTRY RosUmdDeviceDdi::DdiCalcPrivateTessellationShaderSize(
    D3D10DDI_HDEVICE hDevice, 
    const UINT* pCode, 
    const D3D11_1DDIARG_TESSELLATION_IO_SIGNATURES* pSignatures) 
{
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);

    pDevice; // unused
    pCode; // unused
    pSignatures; // unused

    return sizeof(RosUmdTesselationShader);
}

void APIENTRY RosUmdDeviceDdi::DdiCreateHullShader(
    D3D10DDI_HDEVICE hDevice, 
    const UINT* pCode,
    D3D10DDI_HSHADER hShader,
    D3D10DDI_HRTSHADER hRTShader,
    const D3D11_1DDIARG_TESSELLATION_IO_SIGNATURES* pSignatures)
{ 
    RosUmdLogging::Entry(__FUNCTION__);

    RosUmdDevice * pRosUmdDevice = RosUmdDevice::CastFrom(hDevice);

    try
    {
        pRosUmdDevice->CreateTessellationShader(pCode, hShader, hRTShader, pSignatures, D3D11_SB_HULL_SHADER);
    }

    catch (std::exception & e)
    {
        pRosUmdDevice->SetException(e);
    }

    RosUmdLogging::Exit(__FUNCTION__);
}

void APIENTRY RosUmdDeviceDdi::DdiCreateDomainShader(
    D3D10DDI_HDEVICE hDevice,
    const UINT* pCode,
    D3D10DDI_HSHADER hShader,
    D3D10DDI_HRTSHADER hRTShader,
    const D3D11_1DDIARG_TESSELLATION_IO_SIGNATURES* pSignatures)
{ 
    RosUmdLogging::Entry(__FUNCTION__);

    RosUmdDevice * pRosUmdDevice = RosUmdDevice::CastFrom(hDevice);

    try
    {
        pRosUmdDevice->CreateTessellationShader(pCode, hShader, hRTShader, pSignatures, D3D11_SB_DOMAIN_SHADER);
    }

    catch (std::exception & e)
    {
        pRosUmdDevice->SetException(e);
    }

    RosUmdLogging::Exit(__FUNCTION__);
}

void APIENTRY RosUmdDeviceDdi::DdiDestroyShader(
    D3D10DDI_HDEVICE hDevice,
    D3D10DDI_HSHADER hShader) 
{ 
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);

    pDevice->DestroyShader(hShader);
}

void APIENTRY RosUmdDeviceDdi::DdiPsSetShader(D3D10DDI_HDEVICE hDevice, D3D10DDI_HSHADER hShader) { 
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    RosUmdShader * pShader = RosUmdShader::CastFrom(hShader);
    pDevice->SetPixelShader(pShader);
}

void APIENTRY RosUmdDeviceDdi::DdiVsSetShader(D3D10DDI_HDEVICE hDevice, D3D10DDI_HSHADER hShader) 
{
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    RosUmdShader * pShader = RosUmdShader::CastFrom(hShader);
    pDevice->SetVertexShader(pShader);
}

void APIENTRY RosUmdDeviceDdi::DdiGsSetShader(D3D10DDI_HDEVICE hDevice, D3D10DDI_HSHADER hShader) 
{
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    RosUmdShader * pShader = RosUmdShader::CastFrom(hShader);
    pDevice->SetGeometryShader(pShader);
}

void APIENTRY RosUmdDeviceDdi::DdiHsSetShader(D3D10DDI_HDEVICE hDevice, D3D10DDI_HSHADER hShader) 
{
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    RosUmdShader * pShader = RosUmdShader::CastFrom(hShader);
    pDevice->SetHullShader(pShader);
}

void APIENTRY RosUmdDeviceDdi::DdiDsSetShader(D3D10DDI_HDEVICE hDevice, D3D10DDI_HSHADER hShader)
{
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    RosUmdShader * pShader = RosUmdShader::CastFrom(hShader);
    pDevice->SetDomainShader(pShader);
}

void APIENTRY RosUmdDeviceDdi::DdiCsSetShader(D3D10DDI_HDEVICE hDevice, D3D10DDI_HSHADER hShader)
{ 
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    RosUmdShader * pShader = RosUmdShader::CastFrom(hShader);

    pDevice->SetComputeShader(pShader);
}

//
// Blend State
//

SIZE_T APIENTRY RosUmdDeviceDdi::DdiCalcPrivateBlendStateSize(
    D3D10DDI_HDEVICE hDevice, 
    const D3D11_1_DDI_BLEND_DESC* desc)
{ 
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice; // unused
    desc; // unused

    return sizeof(RosUmdBlendState);
}

void APIENTRY RosUmdDeviceDdi::DdiCreateBlendState(
    D3D10DDI_HDEVICE hDevice, 
    const D3D11_1_DDI_BLEND_DESC* desc,
    D3D10DDI_HBLENDSTATE hBlendState, 
    D3D10DDI_HRTBLENDSTATE hRTBlendState)
{ 
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice; // unused

    RosUmdBlendState* pBlendState = new (hBlendState.pDrvPrivate) RosUmdBlendState(desc, hRTBlendState);
    pBlendState; // unused

}

void APIENTRY RosUmdDeviceDdi::DdiDestroyBlendState(
    D3D10DDI_HDEVICE hDevice,
    D3D10DDI_HBLENDSTATE hBlendState)
{ 
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice; // unused

    RosUmdBlendState * pBlendState = RosUmdBlendState::CastFrom(hBlendState);
    pBlendState; // unused
}

void APIENTRY RosUmdDeviceDdi::DdiSetBlendState(
    D3D10DDI_HDEVICE hDevice, 
    D3D10DDI_HBLENDSTATE hBlendState, 
    const FLOAT pBlendFactor[4], 
    UINT sampleMask)
{ 
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    RosUmdBlendState * pBlendState = RosUmdBlendState::CastFrom(hBlendState);
    pDevice->SetBlendState(pBlendState, pBlendFactor, sampleMask);
}

//
// Render Target View
//

SIZE_T APIENTRY RosUmdDeviceDdi::DdiCalcPrivateRenderTargetViewSize(
    D3D10DDI_HDEVICE hDevice, 
    const D3D10DDIARG_CREATERENDERTARGETVIEW* pCreate)
{
    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice; // unused
    pCreate; // unused

    return sizeof(RosUmdRenderTargetView);
}

void APIENTRY RosUmdDeviceDdi::DdiCreateRenderTargetView(
    D3D10DDI_HDEVICE hDevice,
    const D3D10DDIARG_CREATERENDERTARGETVIEW* pCreate,
    D3D10DDI_HRENDERTARGETVIEW hRenderTargetView,
    D3D10DDI_HRTRENDERTARGETVIEW hRTRenderTargetView)
{
    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice; // unused

    RosUmdRenderTargetView * pRenderTargetView = new(hRenderTargetView.pDrvPrivate) RosUmdRenderTargetView(pCreate, hRTRenderTargetView);
    pRenderTargetView; // unused

}

void APIENTRY RosUmdDeviceDdi::DdiDestroyRenderTargetView(
    D3D10DDI_HDEVICE hDevice,
    D3D10DDI_HRENDERTARGETVIEW hRenderTargetView)
{
    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice; // unused

    RosUmdRenderTargetView * pRenderTargetView = RosUmdRenderTargetView::CastFrom(hRenderTargetView);
    pRenderTargetView->~RosUmdRenderTargetView();

}

void APIENTRY RosUmdDeviceDdi::DdiClearRenderTargetView(
    D3D10DDI_HDEVICE hDevice,
    D3D10DDI_HRENDERTARGETVIEW hRenderTargetView,
    FLOAT clearColor[4])
{
    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    RosUmdRenderTargetView * pRenderTargetView = RosUmdRenderTargetView::CastFrom(hRenderTargetView);
    pDevice->ClearRenderTargetView(pRenderTargetView, clearColor);
}

void APIENTRY RosUmdDeviceDdi::DdiSetRenderTargets(
    D3D10DDI_HDEVICE hDevice,
    const D3D10DDI_HRENDERTARGETVIEW* phRenderTargetView,
    UINT NumRTVs,
    UINT RTVNumbertoUnbind,
    D3D10DDI_HDEPTHSTENCILVIEW hDepthStencilView,
    const D3D11DDI_HUNORDEREDACCESSVIEW* phUnorderedAccessView,
    const UINT* pUAVInitialCounts,
    UINT UAVIndex,
    UINT NumUAVs,
    UINT UAVFirsttoSet,
    UINT UAVNumberUpdated)
{
    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);

    pDevice->SetRenderTargets(phRenderTargetView, NumRTVs, RTVNumbertoUnbind, hDepthStencilView, phUnorderedAccessView, pUAVInitialCounts, UAVIndex,
        NumUAVs, UAVFirsttoSet, UAVNumberUpdated);
}

//
// View port
//

void APIENTRY RosUmdDeviceDdi::DdiSetViewports(
    D3D10DDI_HDEVICE hDevice,
    UINT numViewports, 
    UINT clearViewports, 
    const D3D10_DDI_VIEWPORT* pViewports)
{
    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice->SetViewports(numViewports, clearViewports, pViewports);
}

//
// Topology
//

void APIENTRY RosUmdDeviceDdi::DdiIaSetTopology(
    D3D10DDI_HDEVICE hDevice, 
    D3D10_DDI_PRIMITIVE_TOPOLOGY topology)
{
    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice->SetTopology(topology);
}

//
// Draw
//

void APIENTRY RosUmdDeviceDdi::DdiDraw(
    D3D10DDI_HDEVICE hDevice, 
    UINT vertexCount,
    UINT startVertexLocation)
{
    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice->Draw(vertexCount, startVertexLocation);
}

void APIENTRY RosUmdDeviceDdi::DdiDrawIndexed(
    D3D10DDI_HDEVICE hDevice,
    UINT indexCount,
    UINT startIndexLocation,
    INT baseVertexLocation)
{
    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
}

//
// Vertex Buffers
//

void APIENTRY RosUmdDeviceDdi::DdiIaSetVertexBuffers(
    D3D10DDI_HDEVICE hDevice,
    UINT startBuffer,
    UINT numBuffers,
    const D3D10DDI_HRESOURCE* phBuffers,
    const UINT* pStrides, 
    const UINT* pOffsets)
{
    RosUmdLogging::Call(__FUNCTION__); 

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice->SetVertexBuffers(startBuffer, numBuffers, phBuffers, pStrides, pOffsets);
}

//
// Index Buffer
//

void APIENTRY RosUmdDeviceDdi::DdiIaSetIndexBuffer(
    D3D10DDI_HDEVICE hDevice,
    D3D10DDI_HRESOURCE hIndexBuffer,
    DXGI_FORMAT hIndexFormat,
    UINT offset)
{
    RosUmdLogging::Call(__FUNCTION__);

    RosUmdDevice * pDevice = RosUmdDevice::CastFrom(hDevice);
    pDevice->SetIndexBuffer(hIndexBuffer, hIndexFormat, offset);
}

