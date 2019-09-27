package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplySeekDonationBC
	{
		public static const PROTO:String = "ProtoAlliance.ReplySeekDonationBC";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var cdtime:int;
		public var alliance:SeekDonationResp;
		public function ReplySeekDonationBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			cdtime = undefined;
			alliance = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.cdtime = this.cdtime;
			if(this.alliance!= undefined)
			{
				serializeObj.alliance = this.alliance.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplySeekDonationBC
		{
			uid = undefined;
			cdtime = undefined;
			alliance = undefined;
			this.uid = msgObj.uid;
			this.cdtime = msgObj.cdtime;
			if(msgObj.hasOwnProperty("alliance"))
			{
				this.alliance = new SeekDonationResp(package_root).unserialize(msgObj.alliance);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplySeekDonationBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}