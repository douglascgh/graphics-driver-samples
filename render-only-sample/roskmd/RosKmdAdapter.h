#pragma once

#include "RosKmd.h"

#if VC4

#include "Vc4Hw.h"
#include "VC4Ddi.h"

#endif

#include "RosKmdAllocation.h"
#include "RosKmdGlobal.h"

typedef struct __ROSKMERRORCONDITION
{
    union
    {
        struct
        {
            UINT    m_UnSupportedPagingOp           : 1;
            UINT    m_NotifyDmaBufCompletion        : 1;
            UINT    m_NotifyPreemptionCompletion    : 1;
            UINT    m_NotifyDmaBufFault             : 1;
            UINT    m_PreparationError              : 1;
            UINT    m_PagingFailure                 : 1;
        };

        UINT        m_Value;
    };
} ROSKMERRORCONDITION;

typedef struct _ROSDMABUFSTATE
{
    union
    {
        struct
        {
            UINT    m_bRender           : 1;
#if VC4

            UINT    m_bRenderTargetRef  : 1;
            UINT    m_bTileAllocMemRef  : 1;
            UINT    m_bTileStateDataRef : 1;
            UINT    m_NumDmaBufSelfRef  : 5;    // Up to 32 DMA buffer self reference
            UINT    m_HasVC4ClearColors : 1;

#endif
            UINT    m_bPresent          : 1;
            UINT    m_bPaging           : 1;
            UINT    m_bSwCommandBuffer  : 1;
            UINT    m_bPatched          : 1;
            UINT    m_bSubmittedOnce    : 1;
            UINT    m_bRun              : 1;
            UINT    m_bPreempted        : 1;
            UINT    m_bReset            : 1;
            UINT    m_bCompleted        : 1;
        };

        UINT        m_Value;
    };
} ROSDMABUFSTATE;

typedef struct _ROSDMABUFINFO
{
    PBYTE                       m_pDmaBuffer;
    LARGE_INTEGER               m_DmaBufferPhysicalAddress;
    UINT                        m_DmaBufferSize;
    ROSDMABUFSTATE              m_DmaBufState;

#if VC4

    RosKmdAllocation           *m_pRenderTarget;
    UINT                        m_RenderTargetPhysicalAddress;

    D3DDDI_PATCHLOCATIONLIST    m_DmaBufSelfRef[VC4_MAX_DMA_BUFFER_SELF_REF];

    VC4ClearColors              m_VC4ClearColors;

#endif
} ROSDMABUFINFO;

typedef struct _ROSDMABUFSUBMISSION
{
    LIST_ENTRY      m_QueueEntry;
    ROSDMABUFINFO * m_pDmaBufInfo;
    UINT            m_StartOffset;
    UINT            m_EndOffset;
    UINT            m_SubmissionFenceId;
} ROSDMABUFSUBMISSION;

typedef union _RosKmAdapterFlags
{
    struct
    {
        UINT    m_isVC4     : 1;
    };

    UINT        m_value;
} RosKmAdapterFlags;

class RosKmdDdi;

class RosKmAdapter
{
public:

    static NTSTATUS AddAdapter(
        IN_CONST_PDEVICE_OBJECT     PhysicalDeviceObject,
        OUT_PPVOID                  MiniportDeviceContext);

    NTSTATUS SubmitCommand(
        IN_CONST_PDXGKARG_SUBMITCOMMAND     pSubmitCommand);

    NTSTATUS DispatchIoRequest(
        IN_ULONG                    VidPnSourceId,
        IN_PVIDEO_REQUEST_PACKET    VideoRequestPacket);
        
    BOOLEAN InterruptRoutine(
        IN_ULONG        MessageNumber);
        
    NTSTATUS Patch(
        IN_CONST_PDXGKARG_PATCH     pPatch);

    NTSTATUS CreateAllocation(
        INOUT_PDXGKARG_CREATEALLOCATION     pCreateAllocation);

    NTSTATUS DestroyAllocation(
        IN_CONST_PDXGKARG_DESTROYALLOCATION     pDestroyAllocation);

    NTSTATUS QueryAdapterInfo(
        IN_CONST_PDXGKARG_QUERYADAPTERINFO      pQueryAdapterInfo);

    NTSTATUS DescribeAllocation(
        INOUT_PDXGKARG_DESCRIBEALLOCATION       pDescribeAllocation);

    NTSTATUS GetNodeMetadata(
        UINT                            NodeOrdinal,
        OUT_PDXGKARG_GETNODEMETADATA    pGetNodeMetadata);

    NTSTATUS GetStandardAllocationDriverData(
        INOUT_PDXGKARG_GETSTANDARDALLOCATIONDRIVERDATA  pGetStandardAllocationDriverData);

    NTSTATUS
        SubmitCommandVirtual(
            IN_CONST_PDXGKARG_SUBMITCOMMANDVIRTUAL  pSubmitCommandVirtual);

    NTSTATUS
        PreemptCommand(
            IN_CONST_PDXGKARG_PREEMPTCOMMAND    pPreemptCommand);

    NTSTATUS
        RestartFromTimeout();

    NTSTATUS
        CancelCommand(
            IN_CONST_PDXGKARG_CANCELCOMMAND pCancelCommand);

    NTSTATUS
        QueryCurrentFence(
            INOUT_PDXGKARG_QUERYCURRENTFENCE   pCurrentFence);

    NTSTATUS
        ResetEngine(
            INOUT_PDXGKARG_RESETENGINE  pResetEngine);

    NTSTATUS
        QueryEngineStatus(
            INOUT_PDXGKARG_QUERYENGINESTATUS    pQueryEngineStatus);

    NTSTATUS
        QueryDependentEngineGroup(
            INOUT_DXGKARG_QUERYDEPENDENTENGINEGROUP     pQueryDependentEngineGroup);

    NTSTATUS
        GetScanLine(
            INOUT_PDXGKARG_GETSCANLINE  pGetScanLine);

    NTSTATUS
        ControlInterrupt(
            IN_CONST_DXGK_INTERRUPT_TYPE    InterruptType,
            IN_BOOLEAN                      EnableInterrupt);

    NTSTATUS
        CollectDbgInfo(
            IN_CONST_PDXGKARG_COLLECTDBGINFO        pCollectDbgInfo);

    NTSTATUS
        CreateProcess(
            IN DXGKARG_CREATEPROCESS* pArgs);

    NTSTATUS
        DestroyProcess(
            IN HANDLE KmdProcessHandle);

    void
        SetStablePowerState(
            IN_CONST_PDXGKARG_SETSTABLEPOWERSTATE  pArgs);

    NTSTATUS
        CalibrateGpuClock(
            IN UINT32                                   NodeOrdinal,
            IN UINT32                                   EngineOrdinal,
            OUT_PDXGKARG_CALIBRATEGPUCLOCK              pClockCalibration
            );

    NTSTATUS
        Escape(
            IN_CONST_PDXGKARG_ESCAPE        pEscape);

    NTSTATUS
        SetPalette(
            IN_CONST_PDXGKARG_SETPALETTE    pSetPalette);

    NTSTATUS
        SetPointerPosition(
            IN_CONST_PDXGKARG_SETPOINTERPOSITION    pSetPointerPosition);

    NTSTATUS
        SetPointerShape(
            IN_CONST_PDXGKARG_SETPOINTERSHAPE   pSetPointerShape);

    NTSTATUS
        ResetFromTimeout();

    NTSTATUS
        QueryInterface(
            IN_PQUERY_INTERFACE     QueryInterface);

    NTSTATUS
        QueryChildRelations(
            INOUT_PDXGK_CHILD_DESCRIPTOR    ChildRelations,
            IN_ULONG                        ChildRelationsSize);

    NTSTATUS
        QueryChildStatus(
            IN_PDXGK_CHILD_STATUS   ChildStatus,
            IN_BOOLEAN              NonDestructiveOnly);
    NTSTATUS
        QueryDeviceDescriptor(
            IN_ULONG                        ChildUid,
            INOUT_PDXGK_DEVICE_DESCRIPTOR   pDeviceDescriptor);

    NTSTATUS
        SetPowerState(
            IN_ULONG                DeviceUid,
            IN_DEVICE_POWER_STATE   DevicePowerState,
            IN_POWER_ACTION         ActionType);

    NTSTATUS
        SetPowerComponentFState(
            IN UINT              ComponentIndex,
            IN UINT              FState);

    NTSTATUS
        PowerRuntimeControlRequest(
            IN LPCGUID           PowerControlCode,
            IN OPTIONAL PVOID    InBuffer,
            IN SIZE_T            InBufferSize,
            OUT OPTIONAL PVOID   OutBuffer,
            IN SIZE_T            OutBufferSize,
            OUT OPTIONAL PSIZE_T BytesReturned);

    NTSTATUS
        NotifyAcpiEvent(
            IN_DXGK_EVENT_TYPE  EventType,
            IN_ULONG            Event,
            IN_PVOID            Argument,
            OUT_PULONG          AcpiFlags);

    void ResetDevice(void);

    NTSTATUS
        IsSupportedVidPn(
            IN_CONST_HANDLE                 hAdapter,
            INOUT_PDXGKARG_ISSUPPORTEDVIDPN pIsSupportedVidPn);

    NTSTATUS
        RecommendFunctionalVidPn(
            IN_CONST_HANDLE                                     hAdapter,
            IN_CONST_PDXGKARG_RECOMMENDFUNCTIONALVIDPN_CONST    pRecommendFunctionalVidPn);

    NTSTATUS
        EnumVidPnCofuncModality(
            IN_CONST_HANDLE                                     hAdapter,
            IN_CONST_PDXGKARG_ENUMVIDPNCOFUNCMODALITY_CONST     pEnumCofuncModality);

    NTSTATUS
        SetVidPnSourceVisibility(
            IN_CONST_HANDLE                             hAdapter,
            IN_CONST_PDXGKARG_SETVIDPNSOURCEVISIBILITY  pSetVidPnSourceVisibility);

    NTSTATUS
        CommitVidPn(
            IN_CONST_HANDLE                         hAdapter,
            IN_CONST_PDXGKARG_COMMITVIDPN_CONST     pCommitVidPn);

    NTSTATUS
        UpdateActiveVidPnPresentPath(
            IN_CONST_HANDLE                                         hAdapter,
            IN_CONST_PDXGKARG_UPDATEACTIVEVIDPNPRESENTPATH_CONST    pUpdateActiveVidPnPresentPath);

    NTSTATUS
        RecommendMonitorModes(
            IN_CONST_HANDLE                                 hAdapter,
            IN_CONST_PDXGKARG_RECOMMENDMONITORMODES_CONST   pRecommendMonitorModes);

    NTSTATUS
        QueryVidPnHWCapability(
            IN_CONST_HANDLE                             i_hAdapter,
            INOUT_PDXGKARG_QUERYVIDPNHWCAPABILITY       io_pVidPnHWCaps);

private:

    RosKmAdapter(IN_CONST_PDEVICE_OBJECT PhysicalDeviceObject, OUT_PPVOID MiniportDeviceContext);
    ~RosKmAdapter();

    void * operator new(size_t  size);
    void operator delete(void * ptr);

public:

    static RosKmAdapter * Cast(void * ptr)
    {
        RosKmAdapter * rosKmAdapter = reinterpret_cast<RosKmAdapter *>(ptr);

        NT_ASSERT(rosKmAdapter->m_magic == RosKmAdapter::kMagic);

        return rosKmAdapter;
    }

    DXGKRNL_INTERFACE* GetDxgkInterface()
    {
        return &m_DxgkInterface;
    }

    void QueueDmaBuffer(IN_CONST_PDXGKARG_SUBMITCOMMAND pSubmitCommand);

    bool
    ValidateDmaBuffer(
        ROSDMABUFINFO*                  pDmaBufInfo,
        CONST DXGK_ALLOCATIONLIST*      pAllocationList,
        UINT                            allocationListSize,
        CONST D3DDDI_PATCHLOCATIONLIST* pPatchLocationList,
        UINT                            patchAllocationList);

    void
    PatchDmaBuffer(
        ROSDMABUFINFO*                  pDmaBufInfo,
        CONST DXGK_ALLOCATIONLIST*      pAllocationList,
        UINT                            allocationListSize,
        CONST D3DDDI_PATCHLOCATIONLIST* pPatchLocationList,
        UINT                            patchAllocationList);

private:

    friend class RosKmdDdi;

    NTSTATUS Start(
        IN_PDXGK_START_INFO     DxgkStartInfo,
        IN_PDXGKRNL_INTERFACE   DxgkInterface,
        OUT_PULONG              NumberOfVideoPresentSources,
        OUT_PULONG              NumberOfChildren);

    NTSTATUS Stop();

    NTSTATUS BuildPagingBuffer(
        IN_PDXGKARG_BUILDPAGINGBUFFER   pArgs);

private:

    static void WorkerThread(void * StartContext);
    void DoWork(void);
    void DpcRoutine(void);
    void NotifyDmaBufCompletion(ROSDMABUFSUBMISSION * pDmaBufSubmission);
    static BOOLEAN SynchronizeNotifyInterrupt(PVOID SynchronizeContext);
    BOOLEAN SynchronizeNotifyInterrupt();
    ROSDMABUFSUBMISSION * DequeueDmaBuffer(KSPIN_LOCK * pDmaBufQueueLock);
    void ProcessPagingBuffer(ROSDMABUFSUBMISSION * pDmaBufSubmission);
    void ProcessRenderBuffer(ROSDMABUFSUBMISSION * pDmaBufSubmission);
    static void HwDmaBufCompletionDpcRoutine(KDPC *, PVOID, PVOID, PVOID);

    void SubmitControlList(bool bBinningControlist, UINT startAddress, UINT endAddress);
    UINT GetAperturePhysicalAddress(UINT apertureAddress)
    {
        UINT pageIndex = (apertureAddress - ROSD_SEGMENT_APERTURE_BASE_ADDRESS) / kPageSize;

        return ((UINT)m_aperturePageTable[pageIndex])*kPageSize + (apertureAddress & (kPageSize - 1));
    };

    UINT GenerateRenderingControlList(ROSDMABUFINFO *pDmaBufInf);

    void MoveToNextBinnerRenderMemChunk(UINT controlListLength)
    {
        controlListLength = (controlListLength + (kPageSize - 1)) & (~(kPageSize - 1));

#if BINNER_DBG

        m_pRenderingControlList               += controlListLength;
        m_renderingControlListPhysicalAddress += controlListLength;

        if ((m_renderingControlListPhysicalAddress + 64*kPageSize) > (m_controlListPoolPhysicalAddress + VC4_RENDERING_CTRL_LIST_POOL_SIZE))
        {
            m_pRenderingControlList               = m_pControlListPool;
            m_renderingControlListPhysicalAddress = m_controlListPoolPhysicalAddress;
        }

        m_tileAllocationMemoryPhysicalAddress += 64*kPageSize;

        if ((m_tileAllocationMemoryPhysicalAddress + 64*kPageSize) >= m_tileStatePoolPhysicalAddress)
        {
            m_tileAllocationMemoryPhysicalAddress = m_tileAllocPoolPhysicalAddress;
        }

        m_tileStateDataArrayPhysicalAddress += 64 * kPageSize;

        if ((m_tileStateDataArrayPhysicalAddress + 64*kPageSize) >= (RosKmdGlobal::s_videoMemoryPhysicalAddress.LowPart + RosKmdGlobal::s_videoMemorySize))
        {
            m_tileStateDataArrayPhysicalAddress = m_tileStatePoolPhysicalAddress;
        }

#endif
    }

    NTSTATUS SetVC4Power(bool bOn);

private:

    static const size_t kPageSize = 4096;
    static const size_t kPageShift = 12;

    static const size_t kApertureSegmentId = 1;
    static const size_t kApertureSegmentPageCount = 1024;
    static const size_t kApertureSegmentSize = kApertureSegmentPageCount * kPageSize;

    PFN_NUMBER  m_aperturePageTable[kApertureSegmentPageCount];

    static const size_t kVideoMemorySegmentId = 2;

private:

    static const UINT32 kMagic = 'ADPT';

    UINT32                      m_magic;

    RosKmAdapterFlags           m_flags;

    DEVICE_OBJECT              *m_pPhysicalDevice;
    DXGKRNL_INTERFACE           m_DxgkInterface;
    DXGK_START_INFO             m_DxgkStartInfo;

    ROSKMERRORCONDITION         m_ErrorHit;

    PKTHREAD                    m_pWorkerThread;
    KEVENT                      m_workerThreadEvent;
    bool                        m_workerExit;

    // TODO[indyz]: Switch to use the m_DxgkStartInfo::RequiredDmaQueueEntry
    const static UINT           m_maxDmaBufQueueLength = 32;
    ROSDMABUFSUBMISSION         m_dmaBufSubssions[m_maxDmaBufQueueLength];

    LIST_ENTRY                  m_dmaBufSubmissionFree;
    LIST_ENTRY                  m_dmaBufQueue;
    KSPIN_LOCK                  m_dmaBufQueueLock;

    KDPC                        m_hwDmaBufCompletionDpc;
    KEVENT                      m_hwDmaBufCompletionEvent;

    DXGKARGCB_NOTIFY_INTERRUPT_DATA m_interruptData;

    DXGKARG_RESETENGINE        *m_pResetEngine;

    BOOL                        m_bReadyToHandleInterrupt;

    DXGK_DEVICE_INFO            m_deviceInfo;

    BYTE                        m_deviceId[MAX_DEVICE_ID_LENGTH];
    ULONG                       m_deviceIdLength;

#if VC4

    VC4_REGISTER_FILE          *m_pVC4RegFile;
    UINT                        m_localVidMemSegmentSize;

    BYTE                       *m_pRenderingControlList;
    UINT                        m_renderingControlListPhysicalAddress;
    UINT                        m_tileAllocationMemoryPhysicalAddress;
    UINT                        m_tileStateDataArrayPhysicalAddress;

    BYTE                       *m_pControlListPool;
    UINT                        m_controlListPoolPhysicalAddress;
    UINT                        m_tileAllocPoolPhysicalAddress;
    UINT                        m_tileStatePoolPhysicalAddress;

    // Firmware device RPIQ
    PDEVICE_OBJECT              m_pRpiqDevice;

#if GPU_CACHE_WORKAROUND

    UINT                        m_rtSizeJitter;

#endif

    UINT                        m_busAddressOffset;

#endif

public:

    DEVICE_POWER_STATE          m_AdapterPowerDState;
    BOOLEAN                     m_PowerManagementStarted;
    UINT                        m_NumPowerComponents;
    DXGK_POWER_RUNTIME_COMPONENT m_PowerComponents[C_ROSD_GPU_ENGINE_COUNT];
    UINT                         m_EnginePowerFState[C_ROSD_GPU_ENGINE_COUNT];
    
    UINT                        m_NumNodes;
    DXGK_WDDMVERSION            m_WDDMVersion;

public:

    NTSTATUS
        InitializePowerComponentInfo();
        
    NTSTATUS 
        GetNumPowerComponents();

    NTSTATUS
        GetPowerComponentInfo(
            IN UINT ComponentIndex,
            OUT DXGK_POWER_RUNTIME_COMPONENT* pPowerComponent);

};

template<typename TypeCur, typename TypeNext>
void MoveToNextCommand(TypeCur pCurCommand, TypeNext &pNextCommand)
{
    pNextCommand = (TypeNext)(pCurCommand + 1);
}

