package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class CSGetFriendInfoResp
	{
		public static const PROTO:String = "ProtoFriend.CSGetFriendInfoResp";
		public var package_root:*;
		public  var message:*;
		public var type:int;
		public var myuid:int;
		public var folk:Vector.<FolkCPP>;
		public function CSGetFriendInfoResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			type = undefined;
			myuid = undefined;
			folk = new Vector.<FolkCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.type = this.type;
			serializeObj.myuid = this.myuid;
			serializeObj.folk = [];
			for(var i:int = 0;i < this.folk.length;i++)
			{
				serializeObj.folk.push(this.folk[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSGetFriendInfoResp
		{
			type = undefined;
			myuid = undefined;
			folk = new Vector.<FolkCPP>();
			this.type = msgObj.type;
			this.myuid = msgObj.myuid;
			for(var i:int = 0;i < msgObj.folk.length;i++)
			{
				this.folk.push(new FolkCPP(package_root).unserialize(msgObj.folk[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSGetFriendInfoResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}