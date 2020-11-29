package com.skrefi.deer;

        import android.content.Intent;
        import android.os.Bundle;
        import android.util.Log;
        import android.view.View;
        import android.widget.ImageView;
        import android.widget.Toast;

        import com.google.android.gms.tasks.OnFailureListener;
        import com.google.android.gms.tasks.OnSuccessListener;
        import com.google.firebase.auth.FirebaseAuth;
        import com.google.firebase.database.DataSnapshot;
        import com.google.firebase.database.DatabaseError;
        import com.google.firebase.database.DatabaseReference;
        import com.google.firebase.database.FirebaseDatabase;
        import com.google.firebase.database.ValueEventListener;
        import com.skrefi.deer.CommentUtils.OnPostActivity;
        import com.skrefi.deer.PostUtils.Post;
        import com.skrefi.deer.PostUtils.PostActivity;
        import com.skrefi.deer.PostUtils.PostAdapter;

        import java.util.ArrayList;

        import androidx.annotation.NonNull;
        import androidx.appcompat.app.AppCompatActivity;
        import androidx.recyclerview.widget.LinearLayoutManager;
        import androidx.recyclerview.widget.RecyclerView;

public class MainActivity extends AppCompatActivity {

    private RecyclerView mRecyclerView;
    private PostAdapter mAdapter;
    private RecyclerView.LayoutManager mLayoutManager;

    private FirebaseAuth mAuth;
    //private FirebaseUser user;
    private DatabaseReference ref;

    private ImageView deerButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mAuth = FirebaseAuth.getInstance();
        //user = mAuth.getCurrentUser();

        deerButton = findViewById(R.id.deer_Button);

        deerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this, PostActivity.class));
            }
        });

        final ArrayList<Post> postList = new ArrayList<>();

        mRecyclerView = findViewById(R.id.postRecyclerView);
        mRecyclerView.setHasFixedSize(true);
        mLayoutManager = new LinearLayoutManager(this);

        mRecyclerView.setLayoutManager(mLayoutManager);

        ref = FirebaseDatabase.getInstance().getReference().child("posts");

        ref.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Toast.makeText(MainActivity.this, "" + dataSnapshot.getChildrenCount(), Toast.LENGTH_SHORT).show();
                for(DataSnapshot data : dataSnapshot.getChildren()){
                    Post p = data.getValue(Post.class);
                    postList.add(p);
                }

                mAdapter = new PostAdapter(postList);
                mRecyclerView.setAdapter(mAdapter);

                mAdapter.setOnItemClickListener(new PostAdapter.OnItemClickListener() {
                    @Override
                    public void onItemClick(int position) {
                        Post post = postList.get(position);
                        Intent intent = new Intent(MainActivity.this, OnPostActivity.class);
                        intent.putExtra("LINK", post.getPicAvatar());
                        intent.putExtra("TEXT", post.getText());
                        startActivity(intent);
                    }

                    @Override
                    public void onCoolClick(int position) {
                        Post post = postList.get(position);

                    }

                    @Override
                    public void onMehClick(int position) {
                        Post post = postList.get(position);

                    }
                });
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {
                Toast.makeText(MainActivity.this, databaseError.getMessage(), Toast.LENGTH_SHORT).show();
            }
        });
    }
}