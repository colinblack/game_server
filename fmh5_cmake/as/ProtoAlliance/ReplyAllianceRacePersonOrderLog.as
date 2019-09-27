package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyAllianceRacePersonOrderLog
	{
		public static const PROTO:String = "ProtoAlliance.ReplyAllianceRacePersonOrderLog";
		public var package_root:*;
		public  var message:*;
		public var member:Vector.<AllianceRacePersonOrderLogItem>;
		public function ReplyAllianceRacePersonOrderLog(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			member = new Vector.<AllianceRacePersonOrderLogItem>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.member = [];
			for(var i:int = 0;i < this.member.length;i++)
			{
				serializeObj.member.push(this.member[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyAllianceRacePersonOrderLog
		{
			member = new Vector.<AllianceRacePersonOrderLogItem>();
			for(var i:int = 0;i < msgObj.member.length;i++)
			{
				this.member.push(new AllianceRacePersonOrderLogItem(package_root).unserialize(msgObj.member[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyAllianceRacePersonOrderLog
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}