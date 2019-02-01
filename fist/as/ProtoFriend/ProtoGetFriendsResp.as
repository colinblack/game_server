package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGetFriendsResp
	{
		public static const PROTO:String = "ProtoFriend.ProtoGetFriendsResp";
		public var package_root:*;
		public  var message:*;
		public var user:Vector.<RecommendInfo>;
		public function ProtoGetFriendsResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			user = new Vector.<RecommendInfo>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.user = [];
			for(var i:int = 0;i < this.user.length;i++)
			{
				serializeObj.user.push(this.user[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoGetFriendsResp
		{
			user = new Vector.<RecommendInfo>();
			for(var i:int = 0;i < msgObj.user.length;i++)
			{
				this.user.push(new RecommendInfo(package_root).unserialize(msgObj.user[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGetFriendsResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}