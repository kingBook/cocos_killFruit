package com.kingBook.killFruit;

import android.os.Handler;
import android.os.Message;

public class TestHelper {
	
	private static Handler mHandler;
	public static void init(Handler handler){
		TestHelper.mHandler=handler;
	}
	
	public static native void payCallback(String result);//支付结果回调"yes"/"no"
	
	private static void pay(final int money, final String product, final String extData){
		Message msg = mHandler.obtainMessage();
		msg.what = killFruit.PAY;
		
		PayInfo payInfo = new PayInfo();
		payInfo.money = money;
		payInfo.product = product;
		payInfo.extData = extData;
		
		msg.obj = payInfo;
		msg.sendToTarget();
	}
}
