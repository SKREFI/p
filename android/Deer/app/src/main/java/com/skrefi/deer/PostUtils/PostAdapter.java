package com.skrefi.deer.PostUtils;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.skrefi.deer.R;
import com.squareup.picasso.Picasso;

import java.util.ArrayList;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

public class PostAdapter extends RecyclerView.Adapter<PostAdapter.PostViewHolder> {
    private ArrayList<Post> mPostList;
    private OnItemClickListener mListener;

    public interface OnItemClickListener {
        void onItemClick(int position);
        void onCoolClick(int position);
        void onMehClick(int position);
    }

    public void setOnItemClickListener(OnItemClickListener listener){
        mListener = listener;
    }

    public static class PostViewHolder extends RecyclerView.ViewHolder {
        public ImageView mImageView;
        public TextView mTextView;
        public TextView mCoolTextView;
        public TextView mLikesTextView;
        public TextView mMehTextView;

        public PostViewHolder(View itemView, final OnItemClickListener listener){
            super(itemView);
            mImageView = itemView.findViewById(R.id.post_imageView_postAvatar);
            mTextView = itemView.findViewById(R.id.post_textView_postText);
            mCoolTextView = itemView.findViewById(R.id.post_textView_coolButton);
            mLikesTextView = itemView.findViewById(R.id.post_textView_likes);
            mMehTextView = itemView.findViewById(R.id.post_textView_mehButton);

            itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    if (listener != null){
                        int position = getAdapterPosition();
                        if(position != RecyclerView.NO_POSITION){
                            listener.onItemClick(position);
                        }
                    }
                }
            });

            mCoolTextView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    if (listener != null){
                        int position = getAdapterPosition();
                        if(position != RecyclerView.NO_POSITION){
                            listener.onCoolClick(position);
                        }
                    }
                }
            });

            mMehTextView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    if (listener != null){
                        int position = getAdapterPosition();
                        if(position != RecyclerView.NO_POSITION){
                            listener.onMehClick(position);
                        }
                    }
                }
            });
        }
    }

    public PostAdapter(ArrayList<Post> postList){
        mPostList = postList;
    }

    @NonNull
    @Override
    public PostViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.post, parent, false);
        PostViewHolder postViewHolder = new PostViewHolder(v, mListener);
        return postViewHolder;
    }

    @Override
    public void onBindViewHolder(@NonNull PostViewHolder holder, int position) {
        Post post = mPostList.get(position);

        Picasso.get().load(post.getPicAvatar()).into(holder.mImageView);
        holder.mLikesTextView.setText("" + post.getLikes());
        holder.mTextView.setText(post.getText());
    }

    @Override
    public int getItemCount() {
        return mPostList.size();
    }
}
