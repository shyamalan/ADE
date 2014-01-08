

int detect()
{
	//-- 1. Load the cascades
	if( !face_cascade.load( face_cascade_name ) ){
		printf("--(!)Error loading\n");
		return -1;
	};
	//-- 2. Read the video stream
	capture = cvCaptureFromCAM( 0 );
	if( capture ){
		while( true ){
			frame = cvQueryFrame( capture );
			//-- 3. Apply the classifier to the frame
			if( !frame.empty() ){
				Mat frame_gray;

				cvtColor( frame, frame_gray, CV_BGR2GRAY );
				equalizeHist( frame_gray, frame_gray );

				//-- Detect faces
				face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
				return faces.size();
			}
			else{
				printf(" --(!) No captured frame -- Break!");
				return -1;
			}
			int c = waitKey(10);
			if( (char)c == 'c' )
				return -1;
		}
	}
	return 0;
}

float* face_pos(){
	float* pos;
	for( int i = 0; i < faces.size(); i++ ){
		pos[1] = (int)((float)faces[i].x * 25.0 / 107.0);
		pos[2] = (int)((float)faces[i].y * 55.0 / 78.0);
	}
	return pos;
}


