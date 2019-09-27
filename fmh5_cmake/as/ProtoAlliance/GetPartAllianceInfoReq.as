package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class GetPartAllianceInfoReq
	{
		public static const PROTO:String = "ProtoAlliance.GetPartAllianceInfoReq";
		public var package_root:*;
		public  var message:*;
		public var allianceId:Vector.<int>;
		public function GetPartAllianceInfoReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			allianceId = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.allianceId = [];
			for(var i:int = 0;i < this.allianceId.length;i++)
			{
				serializeObj.allianceId.push(this.allianceId[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetPartAllianceInfoReq
		{
			allianceId = new Vector.<int>();
			for(var i:int = 0;i < msgObj.allianceId.length;i++)
			{
				this.allianceId.push(msgObj.allianceId[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetPartAllianceInfoReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}