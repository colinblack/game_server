package com.sanguo.game.server.connectlogic.common.message.ProtoChampionship
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoChampionshipReq
	{
		public static const PROTO:String = "ProtoChampionship.ProtoChampionshipReq";
		public var package_root:*;
		public  var message:*;
		public var battleid:int;
		public var common:BattleCommonCPP;
		public function ProtoChampionshipReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			battleid = undefined;
			common = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.battleid = this.battleid;
			if(this.common!= undefined)
			{
				serializeObj.common = this.common.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoChampionshipReq
		{
			battleid = undefined;
			common = undefined;
			this.battleid = msgObj.battleid;
			if(msgObj.hasOwnProperty("common"))
			{
				this.common = new BattleCommonCPP(package_root).unserialize(msgObj.common);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoChampionshipReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}