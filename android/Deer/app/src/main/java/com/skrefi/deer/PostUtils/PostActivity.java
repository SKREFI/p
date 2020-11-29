package com.skrefi.deer.PostUtils;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.skrefi.deer.MainActivity;
import com.skrefi.deer.R;

public class  PostActivity extends AppCompatActivity {

    private EditText postText;
    private TextView sendButton;

    private FirebaseDatabase database = FirebaseDatabase.getInstance();
    private DatabaseReference myRef = database.getReference();

    private FirebaseAuth firebaseAuth;
    private FirebaseUser user;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_post);

        postText = findViewById(R.id.activityPost_editText_postText);
        sendButton = findViewById(R.id.activityPost_textView_sendButton);

        firebaseAuth = FirebaseAuth.getInstance();
        user = firebaseAuth.getCurrentUser();

        sendButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String text = postText.getText().toString();
                if(text.length() < 10){
                    Toast.makeText(PostActivity.this, "Your post is too small!", Toast.LENGTH_SHORT).show();
                } else {
                    Post post = new Post(text);

                    String key = myRef.push().getKey();

                    post.setPicAvatar("https://robohash.org/" + key + "_" + user.getUid());
                    post.setLikes(0);


                    myRef.child("posts").child(key).setValue(post).addOnSuccessListener(new OnSuccessListener<Void>() {
                        @Override
                        public void onSuccess(Void aVoid) {
                            Toast.makeText(PostActivity.this, "Post successful!", Toast.LENGTH_SHORT).show();
                            finish();
                            startActivity(new Intent(PostActivity.this, MainActivity.class));
                        }
                    }).addOnFailureListener(new OnFailureListener() {
                        @Override
                        public void onFailure(@NonNull Exception e) {
                            Toast.makeText(PostActivity.this, e.getMessage(), Toast.LENGTH_SHORT).show();
                        }
                    });
                }

            }
        });
    }
}
