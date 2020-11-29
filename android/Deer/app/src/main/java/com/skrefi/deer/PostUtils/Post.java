package com.skrefi.deer.PostUtils;

public class Post {

//    private int mUID;
    private String mPicAvatar;
    private String mText;
    private int mLikes;

    public Post() {}

    public Post(String text){
        mText = text;
    }

//    public int getUID() {
//        return mUID;
//    }


    public int getLikes() {
        return mLikes;
    }

    public void setLikes(int mLikes) {
        this.mLikes = mLikes;
    }

    public Post(String text, String img){
        mText = text;
        mPicAvatar = img;
    }

    public String getPicAvatar() {
        return mPicAvatar;
    }

    public String getText() {
        return mText;
    }

//    public void setUID(int uid) {
//        this.mUID = uid;
//    }

    public void setPicAvatar(String picAvatar) {
        this.mPicAvatar = picAvatar;
    }

    public void setText(String text) {
        this.mText = text;
    }
}
