/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.kingBook.killFruit;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.os.Bundle;

import android.os.Message;
import android.os.Handler;
import android.content.Context;
import com.cggame.sdk.CGGameSdk;
import com.cggame.sdk.CallbackInfo;
import com.cggame.sdk.PayCallback;


public class killFruit extends Cocos2dxActivity{
	public static final int PAY = 0x0001;
	private CGGameSdk _ggSdk;
	private Context _myContext;
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		_myContext = this;
     	_ggSdk = CGGameSdk.getInstance();
     	open();
     	TestHelper.init(mHandler);
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// killFruit should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }
    
    public int open(){
    	return _ggSdk.open(this);
    }
    
    public int close(){
    	return _ggSdk.close();
    }
    
    /**
     * pay是Cooguo平台短信充值接口，充值时调用。
     * @param context 应用上下文
     * @param money 充值金额数(限1-3000)单位：分
     * @param product 道具名称
     * @param extData 扩张字段
     * @param payCallback 状态回调对象
     * @return
     */
    public int pay(int money, String product, String extData){
 	   return CGGameSdk.getInstance().pay(_myContext, money, product, extData, getNewPayCallback());
    }
    
    private PayCallback getNewPayCallback(){
 	   PayCallback cb = new PayCallback() {
 			public void invoking(CallbackInfo callbackInfo) {
 				switch (callbackInfo.state) {
 					case -1://处理失败
 						TestHelper.payCallback("no");
 						break;
 					case 0: //处理成功
 						TestHelper.payCallback("yes");
 					break;
 				}
 			}
 		};
 	   return cb;
    }
    
    private Handler mHandler = new Handler(){
    	@Override
		public void handleMessage(Message msg) {
    		switch(msg.what){
				case PAY:
					PayInfo info = (PayInfo)msg.obj;
					pay(info.money,info.product,info.extData);
				break;
			}	
    	}
    };
    
    @Override
    protected void onDestroy(){
 	   close();
 	   super.onDestroy();
    }
    
   
}
