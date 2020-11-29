package com.skrefi.deer.CommentUtils;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
import com.skrefi.deer.R;
import com.squareup.picasso.Picasso;

import java.util.ArrayList;

public class OnPostActivity extends AppCompatActivity {

    private RecyclerView mRecyclerView;
    private RecyclerView.Adapter mAdapter;
    private RecyclerView.LayoutManager mLayoutManager;

    private FirebaseAuth mAuth;
    private FirebaseUser mUser;

    private String link;
    private String text;

    private ImageView mOpAvatar;
    private TextView mTextView, mTextViewReplyButton;
    private EditText mEditTextComment;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_on_post);

        link = getIntent().getStringExtra("LINK");
        text = getIntent().getStringExtra("TEXT");

        mOpAvatar = findViewById(R.id.onPost_imageView_opAvatar);
        mTextView = findViewById(R.id.onPost_textView_postText);

        Picasso.get().load(link).into(mOpAvatar);
        final String key = link.substring(21, 41);
        mTextView.setText(text);

        mAuth = FirebaseAuth.getInstance();
        mUser = mAuth.getCurrentUser();

        mTextViewReplyButton = findViewById(R.id.onPost_textView_replyButton);
        mEditTextComment = findViewById(R.id.onPost_editText_postComment);

        final ArrayList<Comment> commentArrayList = new ArrayList<>();

        mRecyclerView = findViewById(R.id.commentRecyclerView);
        mRecyclerView.setHasFixedSize(true);
        mLayoutManager = new LinearLayoutManager(this);
        mRecyclerView.setLayoutManager(mLayoutManager);

        final DatabaseReference ref = FirebaseDatabase.getInstance().getReference().child("comments").child(key);

        ref.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                commentArrayList.clear();
                for(DataSnapshot data : dataSnapshot.getChildren()){
                    Comment comment = data.getValue(Comment.class);
                    commentArrayList.add(comment);
                    //DEBUG
                    //Toast.makeText(OnPostActivity.this, comment.getText(), Toast.LENGTH_SHORT).show();
                }
                mAdapter = new CommentAdapter(commentArrayList);
                mRecyclerView.setAdapter(mAdapter);
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {
                Toast.makeText(OnPostActivity.this, databaseError.getMessage(), Toast.LENGTH_SHORT).show();
            }
        });

        mTextViewReplyButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if(mEditTextComment.getText().toString().length() < 10){
                    Toast.makeText(OnPostActivity.this, "Your comment is too small", Toast.LENGTH_SHORT).show();
                }else{

                    mEditTextComment.clearFocus();
                    DatabaseReference subRef = FirebaseDatabase.getInstance().getReference().child("comments").child(key);
                    String subKey = subRef.push().getKey();

                    String text = mEditTextComment.getText().toString();
                    Comment comment = new Comment();

                    comment.setPic("https://robohash.org/" + key + "_" + mUser.getUid());
                    //"https://robohash.org/" + key + "?" + mUser.getUid()



                    comment.setReplyToAvatar(link);
                    comment.setText(text);

                    mEditTextComment.getText().clear();

                    if (mEditTextComment != null) {
                        InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
                        imm.hideSoftInputFromWindow(mEditTextComment.getWindowToken(), 0);
                    }

                    subRef.child(subKey).setValue(comment).addOnSuccessListener(new OnSuccessListener<Void>() {
                        @Override
                        public void onSuccess(Void aVoid) {
                            //Toast.makeText(OnPostActivity.this, "Comment successful posted!", Toast.LENGTH_SHORT).show();
                        }
                    }).addOnFailureListener(new OnFailureListener() {
                        @Override
                        public void onFailure(@NonNull Exception e) {
                            Toast.makeText(OnPostActivity.this, e.getMessage(), Toast.LENGTH_SHORT).show();
                        }
                    });

                }
            }
        });
    }
}
