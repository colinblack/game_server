package com.sanguo.game.server.connectlogic.common.message.ProtoMission
{
	import laya.utils.Byte;
	public class GetCurMissionResp
	{
		public static const PROTO:String = "ProtoMission.GetCurMissionResp";
		public var package_root:*;
		public  var message:*;
		public var misssion:Vector.<MissionCPP>;
		public function GetCurMissionResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			misssion = new Vector.<MissionCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.misssion = [];
			for(var i:int = 0;i < this.misssion.length;i++)
			{
				serializeObj.misssion.push(this.misssion[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetCurMissionResp
		{
			misssion = new Vector.<MissionCPP>();
			for(var i:int = 0;i < msgObj.misssion.length;i++)
			{
				this.misssion.push(new MissionCPP(package_root).unserialize(msgObj.misssion[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetCurMissionResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}