package com.sanguo.game.server.connectlogic.common.message.ProtoNPCUser
{
	import laya.utils.Byte;
	public class FriendlyTreeStatusCPP
	{
		public static const PROTO:String = "ProtoNPCUser.FriendlyTreeStatusCPP";
		public var package_root:*;
		public  var message:*;
		public var treestatus:int;
		public var nextwaterts:int;
		public function FriendlyTreeStatusCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			treestatus = undefined;
			nextwaterts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.treestatus = this.treestatus;
			if(this.nextwaterts!= undefined)
			{
				serializeObj.nextwaterts = this.nextwaterts;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):FriendlyTreeStatusCPP
		{
			treestatus = undefined;
			nextwaterts = undefined;
			this.treestatus = msgObj.treestatus;
			if(msgObj.hasOwnProperty("nextwaterts"))
			{
				this.nextwaterts = msgObj.nextwaterts;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FriendlyTreeStatusCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}