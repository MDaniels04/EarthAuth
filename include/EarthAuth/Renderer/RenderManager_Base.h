//
// Created by Morga on 24/11/2026.
//

#ifndef BSDCOUNTER_TXT_RENDERMANAGER_BASE_H
#define BSDCOUNTER_TXT_RENDERMANAGER_BASE_H


namespace LabRat {
    /*
     * Abstract base class for renderer management that provides platform / lib abstraction
     */
    class RenderManager_Base
    {


    public:

        /*Default constructor, abs*/
        RenderManager_Base();

        ~RenderManager_Base();

        /*abstr virt func for updating the renderer (as needed in lib */
        virtual auto UpdateRenderer(const float DeltaTime) -> bool = 0;

        /*abstr virt func for initialising the renderer (as needed)*/
        virtual auto InitialiseRenderer() -> bool = 0;

    };
}
#endif //BSDCOUNTER_TXT_RENDERMANAGER_BASE_H
