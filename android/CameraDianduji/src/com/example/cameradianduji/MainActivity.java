package com.example.cameradianduji;


import java.io.File;
import java.io.FileNotFoundException;
import java.util.Locale;

import net.youmi.android.AdManager;
import net.youmi.android.banner.AdSize;
import net.youmi.android.banner.AdView;
import net.youmi.android.banner.AdViewListener;
import net.youmi.android.spot.SpotDialogListener;
import net.youmi.android.spot.SpotManager;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.provider.MediaStore;
import android.speech.tts.TextToSpeech;
import android.speech.tts.TextToSpeech.OnInitListener;
import android.util.Log;
import android.view.Gravity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MenuItem.OnMenuItemClickListener;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;

import com.googlecode.tesseract.android.TessBaseAPI;

public class MainActivity extends Activity {
	final int MENU_ABOUT =0;
	final int MENU_EXIT =1;
	final int COMMON_DIALOG =2;
	
	private static final int PHOTO_CAPTURE = 0x11;// ����ID
	private static final int PHOTO_RESULT = 0x12;// ���ID

	private static String LANGUAGE = "eng";    //Ĭ������ΪӢ��
	private static String IMG_PATH = getSDPath() + java.io.File.separator
			+ "CameraRead";   //Ĭ��·��

	private static EditText etResult;  //��ʾ���
	private static ImageView ivSelected;  //ѡ���ͼƬ
	private static ImageView ivTreated;//������ͼƬ
	private static Button btnCamera;    
	private static Button btnSelect;
	private static Button btnSpeech;
	private static Button btnTranslate;
	
	private static CheckBox chPreTreat;  //��ֵ���Ի���
	private static RadioGroup radioGroup;  //����ѡ���
	private static String textResult;   //����ַ�
	private static Bitmap bitmapSelected;   //ѡ���λͼƬ
	private static Bitmap bitmapTreated;    //������λͼ
	private static TextToSpeech mSpeech;
	private static final int SHOWRESULT = 0x101;   //ѡ��չʾͼƬID
	private static final int SHOWTREATEDIMG = 0x102;  //����ͼƬ���ID
	

	
	public static Handler myHandler = new Handler() {
         //Handler��Ϣ������ƣ������޸Ľ��
		@Override
		public void handleMessage(Message msg) {  //������Ϣ����
			switch (msg.what) {
			case SHOWRESULT:
				if (textResult.equals(""))    //�ж�ʶ����Ƿ���ͼƬ
					etResult.setText("ʶ��ʧ��");
				else
					etResult.setText(textResult);
				break;
			case SHOWTREATEDIMG:
				etResult.setText("ʶ����......");
				showPicture(ivTreated, bitmapTreated);  //����չʾͼƬ����
				break;
			}
			super.handleMessage(msg);   //������Ϣ
		}

	};

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		AdManager.getInstance(this).init("9439249fe1f0ebb3","75da6023fc761c56",false);
		
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

				// 加载插播资源
				SpotManager.getInstance(this).loadSpotAds();
				SpotManager.getInstance(this).setShowInterval(20);// 设置20秒的显示时间间隔
				SpotManager.getInstance(this).setSpotOrientation(
						SpotManager.ORIENTATION_PORTRAIT);

				// 展示插播广告，可以不调用loadSpot独立使用
				SpotManager.getInstance(MainActivity.this).showSpotAds(
						MainActivity.this, new SpotDialogListener() {
							@Override
							public void onShowSuccess() {
								Log.i("YoumiAdDemo", "展示成功");
							}

							@Override
							public void onShowFailed() {
								Log.i("YoumiAdDemo", "展示失败");
							}

							@Override
							public void onSpotClosed() {
								Log.e("YoumiAdDemo", "插屏关闭");
							}

						}); // //

				// 可以根据需要设置Theme，如下调用，如果无特殊需求，直接调用上方的接口即可
				// SpotManager.getInstance(YoumiAdDemo.this).showSpotAds(YoumiAdDemo.this,
				// android.R.style.Theme_Translucent_NoTitleBar);
				// //
		
		File path = new File(IMG_PATH);   //����ļ�·������
		if (!path.exists()) {
			path.mkdirs();  //���ļ��в����򴴽�
		}
		//��ö���ť����
		etResult = (EditText) findViewById(R.id.et_result);
		ivSelected = (ImageView) findViewById(R.id.iv_selected);
		ivTreated = (ImageView) findViewById(R.id.iv_finshed);
		btnCamera = (Button) findViewById(R.id.btn_Camera);
		btnSelect = (Button) findViewById(R.id.btn_select);
		btnSpeech=(Button) findViewById(R.id.btn_translate);
		btnTranslate=(Button)findViewById(R.id.btn_translate2);
		chPreTreat = (CheckBox) findViewById(R.id.ch_pretreat);
		radioGroup = (RadioGroup) findViewById(R.id.radioGroup1);

		btnCamera.setOnClickListener(new cameraButtonListener());
		btnSelect.setOnClickListener(new selectButtonListener());
		btnTranslate.setOnClickListener(new translateButtonListener());
		btnSpeech.setOnClickListener(new speechButtonListener() );
		btnSpeech.setEnabled(false);
		mSpeech =new TextToSpeech(this, new OnInitListener() {
			
			@Override
			public void onInit(int status) {
				if (status == TextToSpeech.SUCCESS) {
					int result = mSpeech.setLanguage(Locale.ENGLISH);
					if (result == TextToSpeech.LANG_MISSING_DATA
							|| result == TextToSpeech.LANG_NOT_SUPPORTED) {
						Log.e("lanageTag", "not use");
					} else {
						btnSpeech.setEnabled(true);
						mSpeech.speak("", TextToSpeech.QUEUE_FLUSH,
								null);
					}
				}
				
			}
		});
		radioGroup.setOnCheckedChangeListener(new OnCheckedChangeListener() {
			//Ϊ����ѡ�����Ӽ�����
			@Override
			public void onCheckedChanged(RadioGroup group, int checkedId) {
				switch (checkedId) {
				case R.id.english:    //Ӣ��
					LANGUAGE = "eng";
					break;
				case R.id.chinese:
					LANGUAGE = "chi_sim";  //����
					break;
				}
			}

		});

	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		MenuItem about=menu.add(0, MENU_ABOUT, 0, R.string.about);
		about.setOnMenuItemClickListener(new OnMenuItemClickListener() {
			
			@Override
			public boolean onMenuItemClick(MenuItem v) {
				showDialog(COMMON_DIALOG);
				return true;
			}
		});
		MenuItem exit=menu.add(0, MENU_EXIT, 0, R.string.exit);
		exit.setOnMenuItemClickListener(new OnMenuItemClickListener() {
			
			@Override
			public boolean onMenuItemClick(MenuItem item) {
				System.exit(0);
				return true;
			}
		});
		return true;
	}
	@Override
	protected Dialog onCreateDialog(int id) {					
		Dialog dialog = null;									
		switch(id){		
		case COMMON_DIALOG:
			new AlertDialog.Builder(this)
	          .setMessage("������������Ӧ�û���OCR��Ӣ�����԰���ʹ������������")
	          .setPositiveButton("ȷ��",
	                         new DialogInterface.OnClickListener(){
	                                 public void onClick(DialogInterface dialoginterface, int i){
	                                     //��ť�¼�
	                                  }
	                          })
	          .show();			
			break;
		default:
			break;
		}
		return dialog;						
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
			//Activity�ص�����,ִ����Activity�ص�
		if (resultCode == Activity.RESULT_CANCELED) //����ֵ��
			return;

		if (requestCode == PHOTO_CAPTURE) {  //����ֵΪ��ȡͼƬId
			etResult.setText("������ͼƬ��");
			startPhotoCrop(Uri.fromFile(new File(IMG_PATH, "temp.jpg")));
		}

		// ������
		if (requestCode == PHOTO_RESULT) {   //����ֵΪ���ͼƬ
			bitmapSelected = decodeUriAsBitmap(Uri.fromFile(new File(IMG_PATH,
					"temp_cropped.jpg")));  //λͼΪ�ü����Ŀ��ͼƬ
			if (chPreTreat.isChecked())   //�ж��Ƿ���Ҫ��ֵ��
				etResult.setText("Ԥ������......");
			else
				etResult.setText("ʶ����......");
			// ��ʾѡ���ͼƬ
			showPicture(ivSelected, bitmapSelected);  //���ú���չʾͼƬ
			
			new Thread(new Runnable() {  // ���߳�������ʶ��
				@Override
				public void run() {
					if (chPreTreat.isChecked()) {
						bitmapTreated = ImgPretreatment
								.doPretreatment(bitmapSelected);
						Message msg = new Message();
						msg.what = SHOWTREATEDIMG;
						myHandler.sendMessage(msg);
						textResult = doOcr(bitmapTreated, LANGUAGE);
					} else {
						bitmapTreated = ImgPretreatment
								.converyToGrayImg(bitmapSelected);
						Message msg = new Message();
						msg.what = SHOWTREATEDIMG;
						myHandler.sendMessage(msg);
						textResult = doOcr(bitmapTreated, LANGUAGE);
					}
					Message msg2 = new Message();
					msg2.what = SHOWRESULT;
					myHandler.sendMessage(msg2);
				}

			}).start();

		}

		super.onActivityResult(requestCode, resultCode, data);
	}
	
	// ����ʶ��
	class cameraButtonListener implements OnClickListener {
        //���ť�����¼�
		@Override
		public void onClick(View arg0) {
			Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);  
			//��Intent���ô洢��ͼƬ
			intent.putExtra(MediaStore.EXTRA_OUTPUT,
					Uri.fromFile(new File(IMG_PATH, "temp.jpg")));//��ֵ����
			startActivityForResult(intent, PHOTO_CAPTURE);
		}
	};

	
	class selectButtonListener implements OnClickListener {
		// �����ѡȡ��Ƭ���ü�
		@Override
		public void onClick(View v) {
			Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
			intent.addCategory(Intent.CATEGORY_OPENABLE);
			intent.setType("image/*");
			intent.putExtra("crop", "true");
			intent.putExtra("scale", true);
			intent.putExtra("return-data", false);
			intent.putExtra(MediaStore.EXTRA_OUTPUT,
					Uri.fromFile(new File(IMG_PATH, "temp_cropped.jpg")));
			intent.putExtra("outputFormat",
					Bitmap.CompressFormat.JPEG.toString());
			intent.putExtra("noFaceDetection", true); 
			startActivityForResult(intent, PHOTO_RESULT);
		}

	}
	class speechButtonListener implements OnClickListener{
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			mSpeech.speak(etResult.getText().toString(),
					TextToSpeech.QUEUE_FLUSH, null);
		}
	}
	class translateButtonListener implements OnClickListener{

		@Override
		public void onClick(View v) {
			Intent intent = new Intent();   
			intent.setClass(MainActivity.this, Translate.class);   //��������Ŀ��   
			Bundle bundle = new Bundle();                           //����Bundle����   
			bundle.putString("something", etResult.getText().toString().trim());     //װ�����   
			intent.putExtras(bundle);                                //��Bundle����Intent����   
			startActivity(intent);                                     //��ʼ�л� 
			
		}
		
	}
	public void startPhotoCrop(Uri uri) {  //����ϵͳͼƬ�༭���вü�
		Intent intent = new Intent("com.android.camera.action.CROP");
		intent.setDataAndType(uri, "image/*");
		intent.putExtra("crop", "true");
		intent.putExtra("scale", true);
		intent.putExtra(MediaStore.EXTRA_OUTPUT,
				Uri.fromFile(new File(IMG_PATH, "temp_cropped.jpg")));
		intent.putExtra("return-data", false);
		intent.putExtra("outputFormat", Bitmap.CompressFormat.JPEG.toString());
		intent.putExtra("noFaceDetection", true); 
		startActivityForResult(intent, PHOTO_RESULT);
	}
	
	public static void showPicture(ImageView iv, Bitmap bmp){
		iv.setImageBitmap(bmp);// ��ͼƬ��ʾ��view��
	}
	

 	public String doOcr(Bitmap bitmap, String language) {
 		//����ͼƬʶ��,��ʶ��ͼƬ,ʶ������
		TessBaseAPI baseApi = new TessBaseAPI();
		//���tessractʶ����ӿ�
		baseApi.init(getSDPath(), language);
		//��ʼ��
		
		bitmap = bitmap.copy(Bitmap.Config.ARGB_8888, true);

		baseApi.setImage(bitmap);

		String text = baseApi.getUTF8Text();
		//�ı��ַ�����
		baseApi.clear();  //���ӿ�
		baseApi.end();  //����ر�

		return text;  //����ʶ�����ַ�
	}


	public static String getSDPath() {
		//��ȡsd����·��
		File sdDir = null;
		boolean sdCardExist = Environment.getExternalStorageState().equals(
				android.os.Environment.MEDIA_MOUNTED); // �ж�sd���Ƿ����
		if (sdCardExist) {
			sdDir = Environment.getExternalStorageDirectory();// ��ȡ���Ŀ¼
		}
		return sdDir.toString();  //·�����ַ�
	}
	
	private Bitmap decodeUriAsBitmap(Uri uri) {  //λͼ��ȡ��uri����·��
		Bitmap bitmap = null;
		try {
			bitmap = BitmapFactory.decodeStream(getContentResolver()
					.openInputStream(uri));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			return null;
		}
		return bitmap;  //���ظ�λͼ�ļ�
	}

}


