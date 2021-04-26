/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Module.h"
#include "../Utils.h"

/////////////////////////////////////////////////
// Module
////////////////////////////////////////////////

DE_PRIV void NullFunction() {
}

DE_IMPL DeccanModule *DE_ModuleCreate(const char *name) {
    DeccanModule *mod = DE_Alloc(sizeof(DeccanModule), 1);
    mod->AtBeginning = NullFunction;
    mod->AtStep = NullFunction;
    mod->AtPostStep = NullFunction;
    mod->AtEnd = NullFunction;
    return mod;
}

DE_IMPL void DE_ModuleDestroy(DeccanModule *mod) {
    DE_Free(mod);
}

/////////////////////////////////////////////////
// Module System
////////////////////////////////////////////////

DE_IMPL void DE_ModuleSysCreate(DeccanModuleSys *modsys) {
    DE_ArrayCreate(&modsys->mods);
}

DE_IMPL void DE_ModuleSysDestroy(DeccanModuleSys *modsys) {
    for (int i = 0; i < modsys->mods.length; i += 1) {
        DE_ModuleDestroy((DeccanModule *)modsys->mods.data[i]);
    }

    DE_ArrayDestroy(&modsys->mods);
}

DE_IMPL void DE_ModuleSysPush(DeccanModuleSys *modsys, DeccanModule *mod) {
    DE_ArrayAddItem(&modsys->mods, (void *)mod);
}

DE_PRIV void ModuleStage(DeccanModule *mod, DeccanModuleStage stage) {
    switch (stage) {
    case DE_SHELL_ATBEGINNING: mod->AtBeginning(); break;
    case DE_SHELL_ATSTEP: mod->AtStep(); break;
    case DE_SHELL_ATPOSTSTEP: mod->AtPostStep(); break;
    case DE_SHELL_ATEND: mod->AtEnd(); break;
    default: break; /* Huh? */
    }
}

DE_IMPL void DE_ModuleSysIter(DeccanModuleSys *modsys, DeccanModuleStage stage, bool order) {
    if (order) {
        for (int i = 0; i < modsys->mods.length; i += 1) {
            ModuleStage((DeccanModule *)modsys->mods.data[i], stage);
        }
    }
    else {
        for (int i = modsys->mods.length - 1; i >= 0; i -= 1) {
            ModuleStage((DeccanModule *)modsys->mods.data[i], stage);
        }
    }
}