package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyKickOutBC
	{
		public static const PROTO:String = "ProtoAlliance.ReplyKickOutBC";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var alliance:KickOutResp;
		public function ReplyKickOutBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			alliance = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			if(this.alliance!= undefined)
			{
				serializeObj.alliance = this.alliance.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyKickOutBC
		{
			uid = undefined;
			alliance = undefined;
			this.uid = msgObj.uid;
			if(msgObj.hasOwnProperty("alliance"))
			{
				this.alliance = new KickOutResp(package_root).unserialize(msgObj.alliance);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyKickOutBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}