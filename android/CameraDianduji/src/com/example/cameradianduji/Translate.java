package com.example.cameradianduji;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Locale;

import net.youmi.android.banner.AdSize;
import net.youmi.android.banner.AdView;
import net.youmi.android.banner.AdViewListener;

import org.apache.http.HttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONArray;
import org.json.JSONObject;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.speech.tts.TextToSpeech;
import android.speech.tts.TextToSpeech.OnInitListener;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.Toast;

public class Translate extends Activity {
	private EditText et_value;
	private EditText et_reslut;
	private Button btn_tran;
	private Button btn_voice;
	private Button btn_voice2;
	
	private TextToSpeech mySpeech;

	private String YouDaoBaseUrl="http://fanyi.youdao.com/openapi.do";
	private String YouDaoKeyFrom="CameraRead";
	private String YouDaokey="18722181";
	private String YouDaoType="data";
	private String YouDaoDoctype="json";
	private String YouDaoVersion="1.1";
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.translate);
		
		// 实例化LayoutParams(重要)
				FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(
						FrameLayout.LayoutParams.FILL_PARENT,
						FrameLayout.LayoutParams.WRAP_CONTENT);
				// 设置广告条的悬浮位置
				layoutParams.gravity = Gravity.BOTTOM | Gravity.RIGHT; // 这里示例为右下角
				// 实例化广告条
				AdView adView = new AdView(this, AdSize.FIT_SCREEN);
				// 调用Activity的addContentView函数
				this.addContentView(adView, layoutParams);

				// 监听广告条接口
				adView.setAdListener(new AdViewListener() {

					@Override
					public void onSwitchedAd(AdView arg0) {
						Log.i("YoumiAdDemo", "广告条切换");
					}

					@Override
					public void onReceivedAd(AdView arg0) {
						Log.i("YoumiAdDemo", "请求广告成功");

					}

					@Override
					public void onFailedToReceivedAd(AdView arg0) {
						Log.i("YoumiAdDemo", "请求广告失败");
					}
				});

				// 插播接口调用
				// 开发者可以到开发者后台设置展示频率，需要到开发者后台设置页面（详细信息->业务信息->无积分广告业务->高级设置）
				// 自4.03版本增加云控制是否开启防误点功能，需要到开发者后台设置页面（详细信息->业务信息->无积分广告业务->高级设置）
		
		et_value=(EditText)findViewById(R.id.et_value);
		Intent intent = this.getIntent();
		Bundle bundle = intent.getExtras();
		et_value.setText(bundle.getString("something"));
		btn_tran=(Button) findViewById(R.id.btn_tran);

		et_reslut=(EditText) findViewById(R.id.et_result);
		btn_tran.setOnClickListener(new tranListener());

		btn_voice=(Button) findViewById(R.id.btn_voice);
		mySpeech =new TextToSpeech(this, new OnInitListener() {

			@Override
			public void onInit(int status) {
				if (status == TextToSpeech.SUCCESS) {
					int result = mySpeech.setLanguage(Locale.ENGLISH);
					if (result == TextToSpeech.LANG_MISSING_DATA
							|| result == TextToSpeech.LANG_NOT_SUPPORTED) {
						Log.e("lanageTag", "not use");
					} else {
						btn_voice.setEnabled(true);
						mySpeech.speak("", TextToSpeech.QUEUE_FLUSH,
								null);
					}
				}

			}
		});
		btn_voice.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				mySpeech.speak(et_value.getText().toString(),
						TextToSpeech.QUEUE_FLUSH, null);
			}
		});
		
		btn_voice2=(Button) findViewById(R.id.btn_voice2);
		btn_voice2.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				mySpeech.speak(et_reslut.getText().toString(),
						TextToSpeech.QUEUE_FLUSH, null);
			}
		});

	}

	class tranListener implements OnClickListener{
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			String YouDaoSearchContent=et_value.getText().toString().trim();
			if(YouDaoSearchContent.equals("")){
				Toast.makeText(Translate.this, "������Ҫ��ѯ�����ݣ�", Toast.LENGTH_LONG).show();
			}else{

				String YouDaoUrl=YouDaoBaseUrl+"?keyfrom="+YouDaoKeyFrom+"&key="+YouDaokey+"&type="+YouDaoType+
						"&doctype="+YouDaoDoctype+"&version="+YouDaoVersion+"&q="+YouDaoSearchContent;
				try{
					AnalyzingOfJson(YouDaoUrl);

				}catch(Exception e){
					e.printStackTrace();
				}
			}
		}

	}
	private void AnalyzingOfJson(String youDaoUrl) throws Exception {
		// TODO Auto-generated method stub
		HttpGet httpGet= new HttpGet(youDaoUrl);
		HttpResponse httpResponse= new DefaultHttpClient().execute(httpGet);
		if(httpResponse.getStatusLine().getStatusCode()==200){
			BufferedReader input1= new BufferedReader(new InputStreamReader(httpResponse.getEntity().getContent())) ;
			StringBuilder sb= new StringBuilder();

			for(String s=input1.readLine();s!=null;s=input1.readLine()){
				sb.append(s);
			} 
			String result=sb.toString();
			System.out.println("result="+result);
			JSONArray jsonArray= new JSONArray("["+result+"]");
			// String message=null;
			StringBuilder message=new StringBuilder();
			for(int i=0;i<jsonArray.length();i++){
				JSONObject jsonObject= jsonArray.getJSONObject(i);
				if(jsonObject!=null){
					String errorCode=jsonObject.getString("errorCode");

					if(errorCode.equals("0")){      
						String query= jsonObject.getString("query");
						//message=query;
						message.append(query);
						String translation=jsonObject.getString("translation");
						// message+="\t"+translation;
						message.append("\t"+translation);
						//�е��ʵ�-��ʵ�
						if(jsonObject.has("basic")){
							JSONObject basic=jsonObject.getJSONObject("basic");
							if(basic.has("phonetic")){
								String phonetic=basic.getString("phonetic");
								// message+="\n\t"+phonetic;
								message.append("\n\t���꣺["+phonetic+"]");
							}
							if(basic.has("explains")){
								String explains=basic.getString("explains");
								//message+="\n\t"+explains;
								message.append("\n\t"+explains);
							}
						}
						if(jsonObject.has("web")){
							String web=jsonObject.getString("web");
							JSONArray webstring= new JSONArray("["+web+"]");
							// message+="\n�������壺";
							message.append("\n�������壺");
							JSONArray webArray= webstring.getJSONArray(0);
							int count=0;
							while(!webArray.isNull(count)){
								if(webArray.getJSONObject(count).has("key")){
									String key=webArray.getJSONObject(count).getString("key");
									//message+="\n\t<"+(count+1)+">"+key;
									message.append("\n\t<"+(count+1)+">"+key);

								}
								if(webArray.getJSONObject(count).has("value")){
									String value=webArray.getJSONObject(count).getString("value");
									//message+="\n\t "+value;
									message.append("\n\t "+value);

								}
								count++;
							}

						}


					}
					if(errorCode.equals("20")){
						Toast.makeText(getApplicationContext(), "Ҫ������ı���", Toast.LENGTH_LONG).show();
					}
					if(errorCode.equals("30")){
						Toast.makeText(getApplicationContext(), "�޷�������Ч�ķ��� ", Toast.LENGTH_LONG).show();
					}
					if(errorCode.equals("40")){
						Toast.makeText(getApplicationContext(), "��֧����������", Toast.LENGTH_LONG).show();
					}
					if(errorCode.equals("50")){
						Toast.makeText(getApplicationContext(), "��Ч��Key", Toast.LENGTH_LONG).show();
					}
				}else{
					Toast.makeText(getApplicationContext(), "Error", Toast.LENGTH_LONG).show();  
				}
			}

			et_reslut.setText(message.toString());

		}
		else{
			Toast.makeText(getApplicationContext(), "��ȡ�쳣", Toast.LENGTH_LONG).show();
		}
	}



}

