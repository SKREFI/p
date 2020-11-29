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
import com.skrefi.deer.R;

public class RegisterActivity extends AppCompatActivity {

    private EditText email_et, password_et;
    private Button button;
    private FirebaseAuth mAuth;

    private ProgressDialog progressDialog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);

        email_et = findViewById(R.id.email_et_register);
        password_et = findViewById(R.id.password_et_register);
        button = findViewById(R.id.register_b_register);

        progressDialog = new ProgressDialog(this);

        mAuth = FirebaseAuth.getInstance();

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if(isAllGood()){
                    mAuth.createUserWithEmailAndPassword(email_et.getText().toString().trim(), password_et.getText().toString().trim()).addOnCompleteListener(new OnCompleteListener<AuthResult>() {
                        @Override
                        public void onComplete(@NonNull Task<AuthResult> task) {
                            if(task.isSuccessful()){
                                MakeToast("Registration successful");
                                mAuth.signOut();
                                progressDialog.dismiss();
                                finish();
                                startActivity(new Intent(RegisterActivity.this, LoginActivity.class));
                            }
                            else MakeToast("Registration failed");
                        }
                    }).addOnFailureListener(new OnFailureListener() {
                        @Override
                        public void onFailure(@NonNull Exception e) {
                            progressDialog.dismiss();
                            MakeToast(e.getMessage());
                        }
                    });
                }
            }
        });

        TextView goToLogin = findViewById(R.id.goToLogin);
        goToLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
                startActivity(new Intent(RegisterActivity.this, LoginActivity.class));
            }
        });
    }

    private Boolean isAllGood(){

        progressDialog.setMessage("This may take few seconds");
        progressDialog.show();

        Boolean ok = true;

        if(TextUtils.isEmpty(email_et.getText().toString().trim())){
            email_et.requestFocus();
            email_et.setError("Please input an email!");
            ok = false;
        }
        if(TextUtils.isEmpty(password_et.getText().toString().trim())){
            password_et.requestFocus();
            password_et.setError("Please input the password!");
            ok = false;
        }
        return ok;
    }

    public void MakeToast(String text) {
        Toast.makeText(this, text, Toast.LENGTH_LONG).show();
    }

}
