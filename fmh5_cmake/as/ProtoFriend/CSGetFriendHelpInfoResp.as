package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class CSGetFriendHelpInfoResp
	{
		public static const PROTO:String = "ProtoFriend.CSGetFriendHelpInfoResp";
		public var package_root:*;
		public  var message:*;
		public var othuid:Vector.<int>;
		public function CSGetFriendHelpInfoResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			othuid = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othuid = [];
			for(var i:int = 0;i < this.othuid.length;i++)
			{
				serializeObj.othuid.push(this.othuid[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSGetFriendHelpInfoResp
		{
			othuid = new Vector.<int>();
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
		public function decode(buffer:*):CSGetFriendHelpInfoResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}