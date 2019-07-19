package com.example.volfp.morecoins;

        import android.os.Bundle;
        import android.support.v7.app.AppCompatActivity;
        import android.util.Log;
        import android.view.MenuItem;
        import android.view.SurfaceView;
        import android.view.WindowManager;

        import org.opencv.android.JavaCameraView;
        import org.opencv.android.BaseLoaderCallback;
        import org.opencv.android.CameraBridgeViewBase;
        import org.opencv.android.CameraBridgeViewBase.CvCameraViewFrame;
        import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener2;
        import org.opencv.android.LoaderCallbackInterface;
        import org.opencv.android.OpenCVLoader;
        import org.opencv.core.Core;
        import org.opencv.core.CvType;
        import org.opencv.core.Mat;
        import org.opencv.core.Point;
        import org.opencv.core.Scalar;
        import org.opencv.core.Size;
        import org.opencv.photo.Photo;
        import org.opencv.imgproc.Imgproc;

// OpenCV Classes

public class MainActivity_show_camera extends AppCompatActivity implements CvCameraViewListener2 {
    // Used for logging success or failure messages
    private static final String TAG = "OCVSample::Activity";

    // Loads camera view of OpenCV for us to use. This lets us see using OpenCV
    private CameraBridgeViewBase mOpenCvCameraView;

    // Used in Camera selection from menu (when implemented)
    private boolean              mIsJavaCamera = true;
    private MenuItem             mItemSwitchCamera = null;

    // These variables are used (at the moment) to fix camera orientation from 270degree to 0degree
    Mat mRgba;
    Mat mRgbaF;
    Mat mRgbaT;

    Mat interMat;

    Mat kernel;
    int radius;
    Point pt= new Point(0,0);
    Size blursize= new Size(5,5);
    int iMinRadius = 10;
    int iMaxRadius = 400;

    private BaseLoaderCallback mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS:
                {
                    Log.i(TAG, "OpenCV loaded successfully");

                    mOpenCvCameraView.enableView();
                } break;
                default:
                {
                    super.onManagerConnected(status);
                } break;
            }
        }
    };

    public MainActivity_show_camera() {
        Log.i(TAG, "Instantiated new " + this.getClass());
    }



    @Override
    protected void onCreate(Bundle savedInstanceState) {

        Log.i(TAG, "called onCreate");
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        setContentView(R.layout.show_camera);

        mOpenCvCameraView = (JavaCameraView) findViewById(R.id.show_camera_activity_java_surface_view);

        mOpenCvCameraView.setVisibility(SurfaceView.VISIBLE);

        mOpenCvCameraView.setCvCameraViewListener(this);
    }

    @Override
    public void onPause()
    {
        super.onPause();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }

    @Override
    public void onResume()
    {
        super.onResume();
        if (!OpenCVLoader.initDebug()) {
            Log.d(TAG, "Internal OpenCV library not found. Using OpenCV Manager for initialization");
            OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_3_0_0, this, mLoaderCallback);
        } else {
            Log.d(TAG, "OpenCV library found inside package. Using it!");
            mLoaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS);
        }
    }

    public void onDestroy() {
        super.onDestroy();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }

    public void onCameraViewStarted(int width, int height) {

        mRgba = new Mat(height, width, CvType.CV_8UC4);
        interMat = new Mat(height, width, CvType.CV_8UC4);
        mRgbaF = new Mat(height, width, CvType.CV_8UC4);
        mRgbaT = new Mat(width, width, CvType.CV_8UC4);
        kernel =new Mat(1,1, CvType.CV_64F,new Scalar(1));
    }

    public void onCameraViewStopped() {
        mRgba.release();
    }

    public Mat onCameraFrame(CvCameraViewFrame inputFrame) {
        // TODO Auto-generated method stub
        mRgba= inputFrame.rgba();
        // convert image to grayscale
        Imgproc.cvtColor(mRgba, mRgba, Imgproc.COLOR_RGBA2GRAY);

        Imgproc.adaptiveThreshold(mRgba,mRgba,255,Imgproc.ADAPTIVE_THRESH_GAUSSIAN_C,Imgproc.THRESH_BINARY_INV,11,2);
        Imgproc.GaussianBlur(mRgba, mRgba, blursize, 4, 4);
        Photo.fastNlMeansDenoising(mRgba, mRgba, 21, 7, 7);
        //Imgproc.morphologyEx(mRgba,mRgba,Imgproc.MORPH_OPEN,kernel,new Point(-1,-1),5);


//apply houghCircles
     Imgproc.HoughCircles(mRgba, interMat, Imgproc.CV_HOUGH_GRADIENT, 2.0, mRgba.rows() / 8,
                100, /*par2*/150, iMinRadius, iMaxRadius);
       if (interMat.cols() > 0)
            if (interMat.cols() > 0)
            if (interMat.cols() > 0)
            for (int x = 0; x < Math.min(interMat.cols(), 30); x++) {
                double vCircle[] = interMat.get(0,x);
                if (vCircle == null)
                    break;
                pt.x= Math.round(vCircle[0]);
                pt.y = Math.round(vCircle[1]);
                radius = (int)Math.round(vCircle[2]);
                // draw the found circle
                Imgproc.circle(mRgba, pt, radius, new Scalar(100,100,100,1), 8);
         }

        // Rotate mRgba 90 degrees
        //Core.transpose(mRgba, mRgbaT);
        //Imgproc.resize(mRgbaT, mRgbaF, mRgbaF.size(), 0,0, 0);
        //Core.flip(mRgbaF, mRgba, 2);
        return mRgba; // This function must return
    }
}
