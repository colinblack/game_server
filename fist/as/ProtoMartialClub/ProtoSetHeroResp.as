package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoSetHeroResp
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoSetHeroResp";
		public var package_root:*;
		public  var message:*;
		public var setHero:MartialHeroInfo;
		public var incomeStartTs:int;
		public function ProtoSetHeroResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			setHero = undefined;
			incomeStartTs = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.setHero = this.setHero.serialize();
			if(this.incomeStartTs!= undefined)
			{
				serializeObj.incomeStartTs = this.incomeStartTs;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoSetHeroResp
		{
			setHero = undefined;
			incomeStartTs = undefined;
			this.setHero = new MartialHeroInfo(package_root).unserialize(msgObj.setHero);
			if(msgObj.hasOwnProperty("incomeStartTs"))
			{
				this.incomeStartTs = msgObj.incomeStartTs;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoSetHeroResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}