package com.wangxingxing.qqvoicechange

/**
 * author : 王星星
 * date : 2022/5/30 16:12
 * email : 1099420259@qq.com
 * description :
 */
object EffectUtils {

    //音效的类型
    const val MODE_NORMAL = 0
    const val MODE_LUOLI = 1
    const val MODE_DASHU = 2
    const val MODE_JINGSONG = 3
    const val MODE_GAOGUAI = 4
    const val MODE_KONGLING = 5

    external fun fix(path: String, type: Int)

    init {
        System.loadLibrary("qqvoicechange")
    }
}