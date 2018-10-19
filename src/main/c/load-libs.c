#include <jni.h>
#include <android/log.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <cardano_funcs.h>


// Macro: allocate memory for number of type and set memory to NULL
#define ZERO(ptr,bytes)  memset( (void *)ptr, '\0', bytes )
#define MEMORY(number,type)  ZERO( malloc( sizeof(type) * number ), sizeof(type) * number )

#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, "load-libs::", __VA_ARGS__))

JNIEXPORT jstring JNICALL Java_test_cardano_MainActivity_encodeBase58(JNIEnv *env, jobject thiz, jbyteArray javaByteArray) {
 
    clock_t start_t, end_t;
    double cpu_time_used;

    start_t = clock();

    jbyte *bytePtr = (*env)->GetByteArrayElements(env, javaByteArray, NULL);
    jint bytePtrSize = (*env)->GetArrayLength(env, javaByteArray); 

    char *encoded = (char *)MEMORY(1000,char);  // TODO: required size = ceil(log(256^a, 58))

    // call library function
    int status =  my_b58_encode( (uint8_t *)bytePtr, (int)bytePtrSize, encoded );
  
    jstring jEncodedString;
    char *log_msg = (char *)MEMORY(1000,char);
    
    if ( status <0 ) {
         jEncodedString = NULL;
         sprintf(log_msg,"There was an error");
    } else { 
         jEncodedString = (*env)->NewStringUTF(env, encoded);
         sprintf(log_msg,"in (%s), out (%s)",encoded,(char *)bytePtr);
    }
 
    free(encoded); 

    (*env)->ReleaseByteArrayElements(env, javaByteArray, bytePtr, 0);

    end_t = clock();
    cpu_time_used = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    LOGI("encodeBase58 calculation time: %f, %s \n", cpu_time_used, log_msg);
    free(log_msg);

    return jEncodedString;
}

JNIEXPORT jbyteArray JNICALL Java_test_cardano_MainActivity_decodeBase58(JNIEnv *env, jobject thiz, jstring javaEncodedString) {
 
    clock_t start_t, end_t;
    double cpu_time_used;

    start_t = clock();

    const char *encoded = (*env)->GetStringUTFChars(env, javaEncodedString, 0);

    uint8_t *bytePtr = (uint8_t *)MEMORY(1000,uint8_t); // TODO: sized
 
    // call library function
    int status =  my_b58_decode( encoded, bytePtr );
  
    jbyteArray jDecodedBytes = NULL;
    char *log_msg = (char *)MEMORY(1000,char);
    
    if ( status <0 ) {
         jDecodedBytes = NULL;
         sprintf(log_msg,"There was an error");
    } else {
         jDecodedBytes = (*env)->NewByteArray(env, strlen((char*)bytePtr));
         (*env)->SetByteArrayRegion(env,jDecodedBytes,0,strlen((char*)bytePtr),bytePtr);
         sprintf(log_msg,"in (%s), out (%s)",encoded,(char *)bytePtr);
    }
 
    free(bytePtr); 

    (*env)->ReleaseStringUTFChars(env, javaEncodedString, encoded);

    end_t = clock();
    cpu_time_used = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    LOGI("decodeBase58 calculation time: %f, %s \n", cpu_time_used,log_msg);

    return jDecodedBytes;
}


