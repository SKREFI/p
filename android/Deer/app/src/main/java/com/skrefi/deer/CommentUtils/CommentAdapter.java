package com.skrefi.deer.CommentUtils;

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

public class CommentAdapter extends RecyclerView.Adapter<CommentAdapter.CommentViewHolder> {
    private ArrayList<Comment> mCommentList;

    public static class CommentViewHolder extends RecyclerView.ViewHolder {
        public ImageView mMainAvatar;
        public ImageView mReplyAvatar;
        public TextView mCommentText;

        public CommentViewHolder(View itemView){
            super(itemView);
            mMainAvatar = itemView.findViewById(R.id.comment_imageView_commentAvatar);
            mReplyAvatar = itemView.findViewById(R.id.comment_imageView_replyToAvatar);
            mCommentText = itemView.findViewById(R.id.comment_textView_commentText);
        }
    }

    public CommentAdapter(ArrayList<Comment> commentList){
        mCommentList = commentList;
    }

    @NonNull
    @Override
    public CommentViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.comment, parent, false);
        CommentViewHolder commentViewHolder = new CommentViewHolder(v);
        return commentViewHolder;
    }

    @Override
    public void onBindViewHolder(@NonNull CommentViewHolder holder, int position) {
        Comment comment = mCommentList.get(position);

        Picasso.get().load(comment.getPic()).into(holder.mMainAvatar);
        Picasso.get().load(comment.getReplyToAvatar()).into(holder.mReplyAvatar);
        holder.mCommentText.setText(comment.getText());
    }

    @Override
    public int getItemCount() {
        return mCommentList.size();
    }
}
