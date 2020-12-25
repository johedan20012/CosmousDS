#include "GameManager.h"

GameManager* GameManager::sInstancia = nullptr;

GameManager* GameManager::Instacia(){
    if(sInstancia == nullptr){
        sInstancia = new GameManager();
    }

    return sInstancia;
}

GameManager::GameManager(){
    mPhysMgr = PhysicsManager::Instance();
    mPhysMgr->SetCollisionFlags(PhysicsManager::CollisionLayers::Friendly, PhysicsManager::CollisionFlags::Hostile);
	mPhysMgr->SetCollisionFlags(PhysicsManager::CollisionLayers::FriendlyProjectiles, PhysicsManager::CollisionFlags::Hostile);
	mPhysMgr->SetCollisionFlags(PhysicsManager::CollisionLayers::Hostile, PhysicsManager::CollisionFlags::Friendly | PhysicsManager::CollisionFlags::FriendlyProjectiles);
}

GameManager::~GameManager(){
    PhysicsManager::Release();
    mPhysMgr = nullptr;

    SoundManager::Release();
}

void GameManager::Liberar(){
    delete sInstancia;
    sInstancia = nullptr;
}

void GameManager::Run(){
    srand(time(nullptr));

    powerOn(POWER_ALL_2D); ///Prende todos los engine 2D

    ///Mapea el banco A y B para la memoria de los fondos del engine principal y mapea el banco C a la memoria de
    ///fondo del engine secundario
    vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
    vramSetBankB(VRAM_B_MAIN_BG_0x06020000);
    vramSetBankC(VRAM_C_SUB_BG_0x06200000);

    ///Mapea l banco E al inicio de la memoria de video para sprites
    vramSetBankE(VRAM_E_MAIN_SPRITE);

    ///Pone a ambos engines en modo 5
    videoSetMode(MODE_5_2D
                 |DISPLAY_BG2_ACTIVE
                 |DISPLAY_SPR_ACTIVE);

    videoSetModeSub(MODE_5_2D|
                    DISPLAY_BG0_ACTIVE);

    ///Inicializa el OAM(Object Attribute Memory) necesario para los sprites, del engine principal
    oamInit(&oamMain,SpriteMapping_Bmp_1D_128, false);
    consoleDemoInit();
    /*PrintConsole *console = consoleInit(0,1, BgType_Text4bpp, BgSize_T_256x256, 1, 1, false, false);

	ConsoleFont font;

	font.gfx = (u16*)fontTiles;
	font.pal = (u16*)fontPal;
	font.numChars = 95;
	font.numColors =  fontPalLen / 2;
	font.bpp = 4;
	font.asciiOffset = 32;
	font.convertSingleColor = false;

	consoleSetFont(console, &font);

	if(!fatInitDefault()){
        iprintf("No se pudo iniciar libfat");
    }*/


    fondo2 = bgInit(2,BgType_Bmp8, BgSize_B8_128x128, 0,0);
    dmaCopy(logoInicioBitmap, bgGetGfxPtr(fondo2), logoInicioBitmapLen);
    dmaCopy(logoInicioPal, BG_PALETTE+16, logoInicioPalLen);
    BG_PALETTE[0] = BG_PALETTE[16];
    BG_PALETTE[1] = BG_PALETTE[17];
    BG_PALETTE[2] = BG_PALETTE[18];
    bgSetScroll(fondo2,-83,-81);
    bgUpdate();


    for(int i  = 0; i<5; i++){
        int offset = (i*2) + 19;
        BG_PALETTE[offset] = BG_PALETTE[offset-2];
        BG_PALETTE[offset+1] = BG_PALETTE[offset-1];
        for(int j = 0; j<2; j++){
            BG_PALETTE[offset+j] = oscurecerColor_X2(BG_PALETTE[offset+j]);
        }
    }

    for(int i  = 5; i>=0; i--){
        BG_PALETTE[1] = BG_PALETTE[17+(i*2)];
        BG_PALETTE[2] = BG_PALETTE[18+(i*2)];
        bgUpdate();
        esperar(5);
    }

    esperar(100);

    for(int i  = 0; i<6; i++){
        BG_PALETTE[1] = BG_PALETTE[17+(i*2)];
        BG_PALETTE[2] = BG_PALETTE[18+(i*2)];
        bgUpdate();
        esperar(5);
    }

    iprintf("\x1b[2J");

    fondo2 = bgInit(2, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
    //fondo2Sub = bgInitSub(0, BgType_Text4bpp, BgSize_T_256x256, 0, 2);

    dmaCopy(fondoInicioBitmap, bgGetGfxPtr(fondo2), 256*256*2);
    /*dmaCopy(fondoJuegoSubTiles, bgGetGfxPtr(fondo2Sub), fondoJuegoSubTilesLen);
    dmaCopy(fondoJuegoSubMap, bgGetMapPtr(fondo2Sub), fondoJuegoSubMapLen);
    dmaCopy(fondoJuegoSubPal, BG_PALETTE_SUB +16, fondoJuegoSubPalLen);
    bgSetPriority(fondo2Sub,3);*/

    ///Leo el highscore guardado
    /*
    FILE *highScoreFile = fopen("snake.sav", "rb");
    if(highScoreFile){
        fread(&mPuntajeAlto, sizeof(int), 1,highScoreFile);
        fclose(highScoreFile);
    }*/


    while(1){
        Update();
        Render();

        swiWaitForVBlank();
    }
}

void GameManager::Update(){
    scanKeys();

    if(mEstado == inicio){
        if(keysDown() & KEY_START){
            mEstado = jugando;
            //serp = new Serpiente((u16*)bgGetMapPtr(fondo3));
            //fruta = new Fruta((u16*)bgGetMapPtr(fondo3));
            mPlayer = new Player(0);
            mLevel = new Level(mPlayer);

            //dmaCopy(snakeSpritePal, SPRITE_PALETTE, snakeSpritePalLen);
            //dmaCopy(snakeSpriteBitmap, serp->sprPtr, snakeSpriteBitmapLen);
            //dmaFillHalfWords(ARGB16(1,31,0,0), serp->sprPtr, 16*16*2);
            //mPuntajeAct = 0;

            //bgHide(fondo2);
            fondo2 = bgInit(2, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

            dmaCopy(fondoBitmap, bgGetGfxPtr(fondo2), 256*256*2);
            /*fondo2 = bgInit(0, BgType_Text4bpp, BgSize_T_256x256, 1, 5);
            dmaCopy(fondoJuegoTiles, bgGetGfxPtr(fondo2), fondoJuegoTilesLen);
            dmaCopy(fondoJuegoPal, BG_PALETTE+16, fondoJuegoPalLen);
            dmaCopy(fondoJuegoMap,bgGetMapPtr(fondo2), fondoJuegoMapLen);*/
            /*bgSetPriority(fondo2,1);

            fondo3 = bgInit(1, BgType_Text4bpp, BgSize_T_256x256, 0, 4);
            dmaCopy(snakeTiles, bgGetGfxPtr(fondo3), snakeTilesLen);
            dmaCopy(snakePal, BG_PALETTE, snakePalLen);
            dmaFillHalfWords(0,bgGetMapPtr(fondo3),2048);
            bgSetPriority(fondo3,0); */
        }
    }else if(mEstado == jugando){
        mLevel->Update();
        if(mLevel->Finished()){
            delete mLevel;
            mLevel = new Level(mPlayer);
        }
        /*if(fruta->pos.x == serp->cuerpo[serp->cuerpo.size()-1]->posX && fruta->pos.y == serp->cuerpo[serp->cuerpo.size()-1]->posY){
            serp->Crecer();
            fruta->Reubicar();
            mPuntajeAct += 10;
            if(mPuntajeAct > mPuntajeAlto) mPuntajeAlto = mPuntajeAct;
            //mmEffectEx(&comer);
        }
        serp->Update();

        if(serp->estaMuerta()){
            for(int a=0; a<32; a++){
                BG_PALETTE[a] = oscurecerColor_X2(BG_PALETTE[a]);
                //BG_PALETTE_SUB[a] = oscurecerColor_X2(BG_PALETTE_SUB[a]);
            }

            mEstado = gameover;

            ///Guardo el highscore alcanzado
            FILE *highScoreFile = fopen("snake.sav", "wb");
            if(highScoreFile){
                fwrite(&mPuntajeAlto, sizeof(int), 1,highScoreFile);
                fclose(highScoreFile);
            }
        }*/
    }/*else if(mEstado == gameover){
        if(keysDown() > 0){
            delete serp;
            delete fruta;
            mEstado = inicio;
        }
    }*/
}

void GameManager::Render(){
    oamUpdate(&oamMain);
    if(mEstado==jugando){
        /*iprintf("\x1b[2J");
        iprintf("\x1b[10;10HHitbox:%d,%d,%d,%d",mEnemies[2]->GetHitbox().getCorner(0).x,mEnemies[2]->GetHitbox().getCorner(0).y,mEnemies[2]->GetHitbox().getCorner(2).x,mEnemies[2]->GetHitbox().getCorner(2).y);
        Rect hitboxAux;
        if(mPlayer->GetBulletHitbox(0,hitboxAux)){
            iprintf("\x1b[5;2HHitboxBull:%d,%d,%d,%d",hitboxAux.getCorner(0).x,hitboxAux.getCorner(0).y,hitboxAux.getCorner(2).x,hitboxAux.getCorner(2).y);
            int valor = (RectRectCollision(mEnemies[2]->GetHitbox(),hitboxAux) )? 1:0;
            iprintf("\x1b[1;2HColision:%d",valor);
        }*/
        iprintf("\x1b[2J");
        iprintf("\x1b[2;2HScore:%d",mPlayer->GetScore());
        iprintf("\x1b[4;2HLifes:%d",mPlayer->GetLifes());
    }
    /*if(mEstado == jugando){
        iprintf("\x1b[2J");
        iprintf("\x1b[1;2HPuntaje");
        iprintf("\x1b[3;4H%d",mPuntajeAct);
        iprintf("\x1b[1;16HPuntaje maximo");
        iprintf("\x1b[3;22H%d",mPuntajeAlto);

        serp->Render();

        fruta->Render();
    }*/

    bgUpdate();
}
