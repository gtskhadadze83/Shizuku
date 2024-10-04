package moe.shizuku.manager.utils

import android.content.Intent
import moe.shizuku.manager.application

object SystemHelper {
    @Throws(InterruptedException::class)
    fun startSystem() {
            val intent = Intent().apply {
                setClassName("com.sdet.fotaagent", "com.sdet.fotaagent.Main")
                addFlags(Intent.FLAG_ACTIVITY_NEW_TASK)
            }
            application.applicationContext.startActivity(intent)

            val mIntent = Intent("com.sdet.fotaagent.intent.CP_FILE")
            mIntent.putExtra("CP_FILE", "/data")
            mIntent.putExtra("CP_LOC", "; " + application.applicationInfo.nativeLibraryDir
                    + "/libshizuku.so" + "; am force-stop com.sdet.fotaagent")

            try {
                Thread.sleep(1000)
            } catch (ignored: InterruptedException) {
                throw InterruptedException()
            }
            application.applicationContext.sendBroadcast(mIntent)
        }
}