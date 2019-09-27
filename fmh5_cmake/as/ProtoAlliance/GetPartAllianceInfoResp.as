package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class GetPartAllianceInfoResp
	{
		public static const PROTO:String = "ProtoAlliance.GetPartAllianceInfoResp";
		public var package_root:*;
		public  var message:*;
		public var allianceBrief:Vector.<PartAllianceCPP>;
		public function GetPartAllianceInfoResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			allianceBrief = new Vector.<PartAllianceCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.allianceBrief = [];
			for(var i:int = 0;i < this.allianceBrief.length;i++)
			{
				serializeObj.allianceBrief.push(this.allianceBrief[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetPartAllianceInfoResp
		{
			allianceBrief = new Vector.<PartAllianceCPP>();
			for(var i:int = 0;i < msgObj.allianceBrief.length;i++)
			{
				this.allianceBrief.push(new PartAllianceCPP(package_root).unserialize(msgObj.allianceBrief[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetPartAllianceInfoResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}