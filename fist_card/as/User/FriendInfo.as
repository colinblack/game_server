package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class FriendInfo
	{
		public static const PROTO:String = "User.FriendInfo";
		public var package_root:*;
		public  var message:*;
		public var info:Vector.<RecommendInfo>;
		public function FriendInfo(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			info = new Vector.<RecommendInfo>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.info = [];
			for(var i:int = 0;i < this.info.length;i++)
			{
				serializeObj.info.push(this.info[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):FriendInfo
		{
			info = new Vector.<RecommendInfo>();
			for(var i:int = 0;i < msgObj.info.length;i++)
			{
				this.info.push(new RecommendInfo(package_root).unserialize(msgObj.info[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FriendInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}