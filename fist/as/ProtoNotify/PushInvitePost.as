package com.sanguo.game.server.connectlogic.common.message.ProtoNotify
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class PushInvitePost
	{
		public static const PROTO:String = "ProtoNotify.PushInvitePost";
		public var package_root:*;
		public  var message:*;
		public var post:MartialClubItemCpp;
		public function PushInvitePost(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			post = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.post = this.post.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushInvitePost
		{
			post = undefined;
			this.post = new MartialClubItemCpp(package_root).unserialize(msgObj.post);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushInvitePost
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}