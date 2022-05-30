package com.wangxingxing.qqvoicechange

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import androidx.lifecycle.lifecycleScope
import com.blankj.utilcode.constant.PermissionConstants
import com.blankj.utilcode.util.LogUtils
import com.blankj.utilcode.util.PermissionUtils
import com.blankj.utilcode.util.ResourceUtils
import com.blankj.utilcode.util.ToastUtils
import com.wangxingxing.qqvoicechange.databinding.ActivityMainBinding
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import org.fmod.FMOD
import java.io.File

class MainActivity : AppCompatActivity() {

    private val TAG = "MainActivity"

    private lateinit var mDestPath: String

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        FMOD.init(this)
        mDestPath = filesDir.absolutePath + File.separator + "xiaoai.mp3"

        checkPermission()
    }

    fun mFix(btn: View) {
        if (!File(mDestPath).exists()) {
            Log.d(TAG, "mFix: 文件不存在")
            return
        }
        lifecycleScope.launch(Dispatchers.IO) {
            when (btn.id) {
                R.id.ll_normal -> EffectUtils.fix(mDestPath, EffectUtils.MODE_NORMAL)
                R.id.ll_luoli -> EffectUtils.fix(mDestPath, EffectUtils.MODE_LUOLI)
                R.id.ll_dashu -> EffectUtils.fix(mDestPath, EffectUtils.MODE_DASHU)
                R.id.ll_jingsong -> EffectUtils.fix(mDestPath, EffectUtils.MODE_JINGSONG)
                R.id.ll_gaoguai -> EffectUtils.fix(mDestPath, EffectUtils.MODE_GAOGUAI)
                R.id.ll_kongling -> EffectUtils.fix(mDestPath, EffectUtils.MODE_KONGLING)
            }
        }
    }

    private fun init() {
        val isCopySuccess = ResourceUtils.copyFileFromAssets("xiaoai.mp3", mDestPath)
        LogUtils.d("isCopySuccess=$isCopySuccess, destFilePath=$mDestPath")
    }

    private fun checkPermission() {
        PermissionUtils.permissionGroup(PermissionConstants.MICROPHONE, PermissionConstants.STORAGE)
            .rationale{ activity, shouldRequest -> ToastUtils.showShort("请打开权限设置页面授权")}
            .callback(object : PermissionUtils.FullCallback{
                override fun onGranted(granted: MutableList<String>) {
                    LogUtils.d("申请权限通过")
                    init()
                }

                override fun onDenied(
                    deniedForever: MutableList<String>,
                    denied: MutableList<String>
                ) {
                    ToastUtils.showShort("申请权限被拒绝")
                }

            }).request()
    }

    override fun onDestroy() {
        super.onDestroy()
        FMOD.close()
    }

}