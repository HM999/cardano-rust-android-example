package test.cardano;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

public final class MainActivity extends Activity {

    public native String encodeBase58(byte[] byteArrayToEncode);
    public native byte[] decodeBase58(String b58StringToDecode);
    static {
        System.loadLibrary("load-libs");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
    }


    public final void encode(final View view) {

        //String str = "Lambos were promised!";

        String str = ((EditText)findViewById(R.id.encField)).getText().toString();
        byte[] toEncode = str.getBytes(Charset.forName("UTF-8"));

        String encodedString = encodeBase58(toEncode);

        if ( encodedString == null ) {
            encodedString = "** ERROR **";
        }

        Toast.makeText(this, encodedString, Toast.LENGTH_SHORT).show();
    }

    public final void decode(final View view) {

        //String str = "2NEpo7TZRRrLZSi2U";

        String str = ((EditText)findViewById(R.id.decField)).getText().toString();
        byte[] decodedBytes = decodeBase58(str);

        String decodedString;

        if ( decodedBytes == null ) {
            decodedString = "** ERROR **";
        } else {
            try {
                decodedString = new String(decodedBytes, "US-ASCII");
            } catch (Exception e) {
                decodedString = "** ERROR **";
            }
        }

        Toast.makeText(this, decodedString, Toast.LENGTH_SHORT).show();
    }
}
