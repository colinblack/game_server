package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class GetMemberResp
	{
		public static const PROTO:String = "ProtoAlliance.GetMemberResp";
		public var package_root:*;
		public  var message:*;
		public var members:Vector.<AllianceMemberCPP>;
		public var allianceId:int;
		public function GetMemberResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			members = new Vector.<AllianceMemberCPP>();
			allianceId = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.members = [];
			for(var i:int = 0;i < this.members.length;i++)
			{
				serializeObj.members.push(this.members[i].serialize());
			}
			serializeObj.allianceId = this.allianceId;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetMemberResp
		{
			members = new Vector.<AllianceMemberCPP>();
			allianceId = undefined;
			for(var i:int = 0;i < msgObj.members.length;i++)
			{
				this.members.push(new AllianceMemberCPP(package_root).unserialize(msgObj.members[i]));
			}
			this.allianceId = msgObj.allianceId;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetMemberResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}