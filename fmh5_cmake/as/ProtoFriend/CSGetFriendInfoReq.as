package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class CSGetFriendInfoReq
	{
		public static const PROTO:String = "ProtoFriend.CSGetFriendInfoReq";
		public var package_root:*;
		public  var message:*;
		public var type:int;
		public var myuid:int;
		public var othuid:Vector.<int>;
		public function CSGetFriendInfoReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			type = undefined;
			myuid = undefined;
			othuid = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.type = this.type;
			serializeObj.myuid = this.myuid;
			serializeObj.othuid = [];
			for(var i:int = 0;i < this.othuid.length;i++)
			{
				serializeObj.othuid.push(this.othuid[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSGetFriendInfoReq
		{
			type = undefined;
			myuid = undefined;
			othuid = new Vector.<int>();
			this.type = msgObj.type;
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
		public function decode(buffer:*):CSGetFriendInfoReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}