package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoRefreshResp
	{
		public static const PROTO:String = "ProtoBattle.ProtoRefreshResp";
		public var package_root:*;
		public  var message:*;
		public var fig:String;
		public var name:String;
		public var hero:Vector.<HeroBaseInfoCPP>;
		public function ProtoRefreshResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			fig = undefined;
			name = undefined;
			hero = new Vector.<HeroBaseInfoCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.fig!= undefined)
			{
				serializeObj.fig = this.fig;
			}
			serializeObj.name = this.name;
			serializeObj.hero = [];
			for(var i:int = 0;i < this.hero.length;i++)
			{
				serializeObj.hero.push(this.hero[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoRefreshResp
		{
			fig = undefined;
			name = undefined;
			hero = new Vector.<HeroBaseInfoCPP>();
			if(msgObj.hasOwnProperty("fig"))
			{
				this.fig = msgObj.fig;
			}
			this.name = msgObj.name;
			for(var i:int = 0;i < msgObj.hero.length;i++)
			{
				this.hero.push(new HeroBaseInfoCPP(package_root).unserialize(msgObj.hero[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoRefreshResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}