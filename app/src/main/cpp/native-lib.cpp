#include <jni.h>
#include "inc/fmod.hpp"
#include <unistd.h>

#include <android/log.h>

#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,"wxx",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"wxx",FORMAT,##__VA_ARGS__);

#define MODE_NORMAL 0
#define MODE_LUOLI 1
#define MODE_DASHU 2
#define MODE_JINGSONG 3
#define MODE_GAOGUAI 4
#define MODE_KONGLING 5

using namespace FMOD;

extern "C"
JNIEXPORT void JNICALL
Java_com_wangxingxing_qqvoicechange_EffectUtils_fix(JNIEnv *env, jobject thiz, jstring path_jstr,
                                                    jint type) {
    const char *path_cstr = env->GetStringUTFChars(path_jstr, nullptr);
    LOGI("%s", path_cstr);
    System *system;
    Sound *sound;
    Channel *channel;
    DSP *dsp;
    float frequency = 0;
    bool playing = true;
    try {
        //初始化
        System_Create(&system);
        system->init(32, FMOD_INIT_NORMAL, nullptr);
        //创建声音
        system->createSound(path_cstr, FMOD_DEFAULT, nullptr, &sound);

        switch (type) {
            //原声播放
            case MODE_NORMAL:
                system->playSound(sound, nullptr, false, &channel);
                LOGI("%s", "fix normal");
                break;

            case MODE_LUOLI:
                //萝莉
                //DSP digital signal process
                //dsp -> 音效 创建fmod中预定义好的音效
                //FMOD_DSP_TYPE_PITCHSHIFT dsp，提升或者降低音调用的一种音效
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //设置音调的参数
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 2.5);
                system->playSound(sound, nullptr, false, &channel);
                //添加到channel
                channel->addDSP(0, dsp);
                LOGI("%s", "fix luoli")
                break;

            case MODE_DASHU:
                //大叔
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //设置音调的参数
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.8);
                system->playSound(sound, nullptr, false, &channel);
                //添加到channel
                channel->addDSP(0, dsp);
                LOGI("%s", "fix dashu");
                break;

            case MODE_GAOGUAI:
                //搞怪
                //提高说话的速度
                system->playSound(sound, nullptr, false, &channel);
                channel->getFrequency(&frequency);
                frequency = frequency * 1.6;
                channel->setFrequency(frequency);
                LOGI("%s", "fix gaoguai");
                break;

            case MODE_KONGLING:
                //空灵
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 20);
                system->playSound(sound, nullptr, false, &channel);
                channel->addDSP(0, dsp);
                LOGI("%s", "fix kongling");
                break;
        }
    } catch (...) {
        LOGE("%s", "发生异常")
        goto end;
    }

    system->update();

    //单位是微秒
    //每秒钟判断下是否在播放
    while (playing) {
        channel->isPlaying(&playing);
        usleep(1000 * 1000);
    }
    goto end;
    end:
    //释放资源
    sound->release();
    system->close();
    system->release();
    env->ReleaseStringUTFChars(path_jstr, path_cstr);
}