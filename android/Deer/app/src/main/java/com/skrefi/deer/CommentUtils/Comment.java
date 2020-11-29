package com.skrefi.deer.CommentUtils;

public class Comment {

    private String mText;
    private String mPic;
    private String mReplyToAvatar;

    public Comment(){}

    public Comment(String text, String pic){
        mText = text;
        mPic = pic;

    }

    public String getReplyToAvatar() {
        return mReplyToAvatar;
    }

    public void setReplyToAvatar(String replyToAvatar) {
        this.mReplyToAvatar = replyToAvatar;
    }

    public String getText() {
        return mText;
    }

    public void setText(String text) {
        this.mText = text;
    }

    public String getPic() {
        return mPic;
    }

    public void setPic(String pic) {
        this.mPic = pic;
    }
}
