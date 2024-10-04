package moe.shizuku.manager.starter;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

import androidx.annotation.Nullable;
import moe.shizuku.manager.utils.SystemHelper;

public class StartSystemService extends Service {
    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId)  {
        try {
            SystemHelper.INSTANCE.startSystem();
        } catch (InterruptedException ignored) {}

        stopSelf();
        return super.onStartCommand(intent, flags, startId);
    }
}
