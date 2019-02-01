package com.sanguo.game.server.connectlogic.common.message.ProtoChampionship
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoChampionshipResp
	{
		public static const PROTO:String = "ProtoChampionship.ProtoChampionshipResp";
		public var package_root:*;
		public  var message:*;
		public var isAttacker:int;
		public var common:ProtoBattleCPP;
		public function ProtoChampionshipResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			isAttacker = undefined;
			common = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.isAttacker = this.isAttacker;
			serializeObj.common = this.common.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoChampionshipResp
		{
			isAttacker = undefined;
			common = undefined;
			this.isAttacker = msgObj.isAttacker;
			this.common = new ProtoBattleCPP(package_root).unserialize(msgObj.common);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoChampionshipResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}