#pragma once

#include "SampleBase.hpp"
#include "BasicMath.hpp"
#include "FirstPersonCamera.hpp"
#include <vector>
#include <random>

namespace Diligent
{

namespace HLSL
{
#include "../assets/structures.fxh"
}

class Tutorial21_RayTracing final : public SampleBase
{
public:
    virtual void ModifyEngineInitInfo(const ModifyEngineInitInfoAttribs& Attribs) override final;
    virtual void Initialize(const SampleInitInfo& InitInfo) override final;

    virtual void Render() override final;
    virtual void Update(double CurrTime, double ElapsedTime) override final;

    virtual const Char* GetSampleName() const override final { return "Tutorial21: Ray tracing"; }

    virtual void WindowResize(Uint32 Width, Uint32 Height) override final;

private:
    void CreateRayTracingPSO();
    void CreateGraphicsPSO();
    void CreateCubeBLAS();
    void CreateProceduralBLAS();
    void UpdateTLAS();
    void CreateSBT();
    void LoadTextures();
    void UpdateUI();

    static constexpr int NumTextures = 4;
    static constexpr int NumCubes    = 4;

    RefCntAutoPtr<IBuffer> m_CubeAttribsCB;
    RefCntAutoPtr<IBuffer> m_BoxAttribsCB;
    RefCntAutoPtr<IBuffer> m_ConstantsCB;

    RefCntAutoPtr<IPipelineState>         m_pRayTracingPSO;
    RefCntAutoPtr<IShaderResourceBinding> m_pRayTracingSRB;

    RefCntAutoPtr<IPipelineState>         m_pImageBlitPSO;
    RefCntAutoPtr<IShaderResourceBinding> m_pImageBlitSRB;

    RefCntAutoPtr<IBottomLevelAS>      m_pCubeBLAS;
    RefCntAutoPtr<IBottomLevelAS>      m_pProceduralBLAS;
    RefCntAutoPtr<ITopLevelAS>         m_pTLAS;
    RefCntAutoPtr<IBuffer>             m_InstanceBuffer;
    RefCntAutoPtr<IBuffer>             m_ScratchBuffer;
    RefCntAutoPtr<IShaderBindingTable> m_pSBT;

    int                      m_NumScatterSpheres = 0;
    int m_NumScatterCubes   = 0; // N�mero de cubos peque�os

    static constexpr int     MaximumSmallSpheres = 50;
    static constexpr int MaximumSmallCubes   = 10; // M�ximo n�mero de cubos peque�os

    std::vector<float3>      m_ScatterSpherePositions;
    std::vector<float3> m_ScatterCubePositions; // Posiciones de los cubos

    std::mt19937             m_Rng{std::random_device{}()};
    Uint32                   m_MaxRecursionDepth     = 8;
    const double             m_MaxAnimationTimeDelta = 1.0 / 60.0;
    float                    m_AnimationTime         = 0.0f;
    HLSL::Constants          m_Constants             = {};
    bool                     m_EnableCubes[NumCubes] = {true, true, true, true};
    bool                     m_Animate               = true;
    float                    m_DispersionFactor      = 0.1f;
    std::vector<std::string> m_ScatterSphereNames;
    std::vector<std::string> m_ScatterCubeNames; // Nombres de los cubos




    FirstPersonCamera m_Camera;

    TEXTURE_FORMAT          m_ColorBufferFormat = TEX_FORMAT_RGBA8_UNORM;
    RefCntAutoPtr<ITexture> m_pColorRT;
};

} // namespace Diligent