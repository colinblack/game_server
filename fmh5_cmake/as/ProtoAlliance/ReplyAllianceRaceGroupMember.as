package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyAllianceRaceGroupMember
	{
		public static const PROTO:String = "ProtoAlliance.ReplyAllianceRaceGroupMember";
		public var package_root:*;
		public  var message:*;
		public var member:Vector.<AllianceRaceGroupMember>;
		public function ReplyAllianceRaceGroupMember(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			member = new Vector.<AllianceRaceGroupMember>();
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
		public function unserialize(msgObj:*):ReplyAllianceRaceGroupMember
		{
			member = new Vector.<AllianceRaceGroupMember>();
			for(var i:int = 0;i < msgObj.member.length;i++)
			{
				this.member.push(new AllianceRaceGroupMember(package_root).unserialize(msgObj.member[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyAllianceRaceGroupMember
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}