package net.saaltink.game;

import org.libsdl.app.SDLActivity; 

import android.content.res.*; 
import android.os.*;
import android.view.*;

public class PassPerfectActivity extends SDLActivity
{
    // Setup
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    
        getWindow().getDecorView().setSystemUiVisibility(
                  View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_FULLSCREEN
                | View.SYSTEM_UI_FLAG_IMMERSIVE);
                
        mgr = getResources().getAssets();
        nativeLoad(mgr);
    }

    // Loading Assets with fopen: http://www.50ply.com/blog/2013/01/19/loading-compressed-android-assets-with-file-pointer
    private AssetManager mgr;
    private static native void nativeLoad(AssetManager mgr);
}
