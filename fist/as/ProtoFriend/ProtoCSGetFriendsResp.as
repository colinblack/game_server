package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSGetFriendsResp
	{
		public static const PROTO:String = "ProtoFriend.ProtoCSGetFriendsResp";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var info:Vector.<RecommendInfo>;
		public function ProtoCSGetFriendsResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myuid = undefined;
			info = new Vector.<RecommendInfo>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			serializeObj.info = [];
			for(var i:int = 0;i < this.info.length;i++)
			{
				serializeObj.info.push(this.info[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSGetFriendsResp
		{
			myuid = undefined;
			info = new Vector.<RecommendInfo>();
			this.myuid = msgObj.myuid;
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
		public function decode(buffer:*):ProtoCSGetFriendsResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}