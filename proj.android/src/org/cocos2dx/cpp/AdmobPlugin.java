package org.cocos2dx.cpp;

import android.app.Activity;
import android.util.Log;
import android.view.View;
import android.view.Gravity;

import android.graphics.Color;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;


import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.InterstitialAd;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.AdSize;

import org.cocos2dx.lib.Cocos2dxActivity;

public class AdmobPlugin {
	private static Cocos2dxActivity activity;
    private static final String TAG = "cocos2d";
	private static InterstitialAd interstitial;
	private static AdView adView;
	
	private final static String MY_INTERSTITIAL_ID = "ca-app-pub-21321321312312423123";
	private final static String MY_BANNER_ID = "ca-app-pub-243243242343253434324";
	
	public static void setActivity(Cocos2dxActivity act){
		activity = act;
	}
	
	public static void pause(){
		
		  //Log.i(TAG, "pause");
		  
	    if (adView != null) {
			  //Log.i(TAG, "adview.pause");
	             adView.pause();
	           }
		
	}
	public static void destroy(){
		  //Log.i(TAG, "destroy");
	    if (adView != null) {
			 //Log.i(TAG, "adview.destroy");
	             adView.destroy();
				
	           }
		
			 
	}
	public static void resume(){
		  //Log.i(TAG, "resume");
	    if (adView != null) {
			  //Log.i(TAG, "adview.resume");
	             adView.resume();
	           }
		
	}
	public static void showBanner(){
		activity.runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				if(adView == null){
					try{
						
				            adView = new AdView(activity);
				            adView.setAdSize(AdSize.SMART_BANNER);
				            adView.setAdUnitId(MY_BANNER_ID);
							
							
							RelativeLayout relativeLayout=new RelativeLayout(activity);

							//TO access mFrameLayout in Cocos2d-V3.3 make it public!!
							activity.mFrameLayout.addView( relativeLayout );
							 
						//Banner at the bottom		
							RelativeLayout.LayoutParams adViewParams = new RelativeLayout.LayoutParams(
							AdView.LayoutParams.WRAP_CONTENT,
							AdView.LayoutParams.WRAP_CONTENT);
							adViewParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
							relativeLayout.addView(adView, adViewParams);
					        				
				          								
			        }catch (Exception e) {
			            Log.e("AdmobPlugin", e.toString());
			        }
				}
				
				//Nexus7 device
				//AdRequest request = new AdRequest.Builder().addTestDevice("E5FDDF2B808A6724F12238F571356547").build();
				AdRequest request = new AdRequest.Builder().build();
				adView.loadAd(request);
				//Hack so that the banner is displayed at startup of the app??!!!!
			    adView.setBackgroundColor(Color.BLACK); 
			    adView.setBackgroundColor(0);  
				//---------------------------------------------------------------
				adView.setVisibility(View.VISIBLE);
			}
		});
	}
	
	public static void hideBanner(){
		activity.runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				if(adView != null){
					adView.setVisibility(View.GONE);
				}
			}
		});
	}
	
	public static void showInterstitial(){
		activity.runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				interstitial = new InterstitialAd(activity);
			    interstitial.setAdUnitId(MY_INTERSTITIAL_ID);
			    AdRequest adRequest = new AdRequest.Builder().build();
				//Nexus7 device
				//AdRequest adRequest = new AdRequest.Builder().addTestDevice("E5FDDF2B808A6724F12238F571356547").build();
			    interstitial.loadAd(adRequest);
			    
			    interstitial.setAdListener(new AdListener() {
			    	@Override
			    	public void onAdLoaded() {
			    		activity.runOnUiThread(new Runnable() {
							
							@Override
							public void run() {
								interstitial.show();
							}
						});
			    	}
				});
			}
		});
	}
}
