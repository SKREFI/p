package com.skrefi.deer.Account;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.skrefi.deer.MainActivity;
import com.skrefi.deer.R;

public class LoginActivity extends AppCompatActivity {

    private Button login_b;
    private EditText email_et;
    private EditText password_et;
    private FirebaseAuth mAuth;

    private ProgressDialog progressDialog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        login_b = findViewById(R.id.login_b_login);
        email_et = findViewById(R.id.email_et_login);
        password_et = findViewById(R.id.password_et_login);

        mAuth = FirebaseAuth.getInstance();
        progressDialog = new ProgressDialog(this);
        FirebaseUser user = mAuth.getCurrentUser();

        if(user != null){
            finish();
            startActivity(new Intent(LoginActivity.this, MainActivity.class));
        }

        login_b.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!isAllGood(email_et.getText().toString().trim(), password_et.getText().toString().trim())){
                    progressDialog.dismiss();
                }
            }
        });

        TextView goToRegister = findViewById(R.id.goToRegister);
        goToRegister.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
                startActivity(new Intent(LoginActivity.this, RegisterActivity.class));
            }
        });
    }


    private Boolean isAllGood(String userName, String userPassword) {

        progressDialog.setMessage("This may take few seconds");
        progressDialog.show();

        Boolean ok = true;
        if (TextUtils.isEmpty(email_et.getText().toString().trim())) {
            email_et.requestFocus();
            email_et.setError("Please input your email!");
            ok = false;
        }
        if (TextUtils.isEmpty(password_et.getText().toString().trim())) {
            password_et.requestFocus();
            password_et.setError("Please input your password!");
            ok = false;
        }

        if(!ok) return ok;

        mAuth.signInWithEmailAndPassword(userName, userPassword).addOnCompleteListener(new OnCompleteListener<AuthResult>() {
            @Override
            public void onComplete(@NonNull Task<AuthResult> task) {
                if(task.isSuccessful()){
                    progressDialog.dismiss();
                    MakeToast("Login successful");
                    finish();
                    startActivity(new Intent(LoginActivity.this, MainActivity.class));
                }else{
                    progressDialog.dismiss();
                    //MakeToast("Login unsuccessful, please check your details!");
                }
            }
        }).addOnFailureListener(new OnFailureListener() {
            @Override
            public void onFailure(@NonNull Exception e) {
                MakeToast(e.getMessage()); //Display the error message it gets from the Firebase
            }
        });

        return ok;
    }

    public void MakeToast(String text) {
        Toast.makeText(this, text, Toast.LENGTH_LONG).show();
    }
}
