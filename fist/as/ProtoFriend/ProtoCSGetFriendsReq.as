package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSGetFriendsReq
	{
		public static const PROTO:String = "ProtoFriend.ProtoCSGetFriendsReq";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var othuid:Vector.<int>;
		public function ProtoCSGetFriendsReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myuid = undefined;
			othuid = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			serializeObj.othuid = [];
			for(var i:int = 0;i < this.othuid.length;i++)
			{
				serializeObj.othuid.push(this.othuid[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSGetFriendsReq
		{
			myuid = undefined;
			othuid = new Vector.<int>();
			this.myuid = msgObj.myuid;
			for(var i:int = 0;i < msgObj.othuid.length;i++)
			{
				this.othuid.push(msgObj.othuid[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSGetFriendsReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}