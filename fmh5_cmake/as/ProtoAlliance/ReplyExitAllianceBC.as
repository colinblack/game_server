package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyExitAllianceBC
	{
		public static const PROTO:String = "ProtoAlliance.ReplyExitAllianceBC";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var aid:int;
		public var alliance:ExitAllianceResp;
		public function ReplyExitAllianceBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			aid = undefined;
			alliance = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.aid = this.aid;
			if(this.alliance!= undefined)
			{
				serializeObj.alliance = this.alliance.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyExitAllianceBC
		{
			uid = undefined;
			aid = undefined;
			alliance = undefined;
			this.uid = msgObj.uid;
			this.aid = msgObj.aid;
			if(msgObj.hasOwnProperty("alliance"))
			{
				this.alliance = new ExitAllianceResp(package_root).unserialize(msgObj.alliance);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyExitAllianceBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}